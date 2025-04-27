import sys, re, os
import numpy as np
import sympy as sp
from math import sqrt
from collections import Counter

import plonka

def dotx(y, matrix, x, code):
    calc = sp.Matrix(matrix) * sp.Matrix(x)
    if not (isinstance(calc, list) or isinstance(calc, sp.Matrix)):
        calc = [calc]
    for ij in zip(y, calc):
        code.append(ij)
    return y

call_num = 0

def next_syms(x):
    n = len(x)
    x0s = str(x[0])
    global call_num
    prefix = 'x%x_' % call_num
    call_num += 1
    return sp.Matrix([sp.Symbol('%s%xx' % (prefix, i)) for i in range(n)])

def tfm_run(name, y, x, code, scale_factor=None):
    neq2_mat, n_delay, b, v1_tfm, v2_tfm, hvec_size_add, modified_matrix = plonka.tfm_props[name]
    n_orig = len(x)
    n = n_orig + n_delay
    n1 = n / 2
    if scale_factor is None:
        scale_factor = 1./sqrt(n>>modified_matrix)
    if n == 2:
        return dotx(y, scale_factor * neq2_mat, x, code)
    elif n >= 4:
        u = dotx(next_syms(x), plonka.sqrt2 * plonka.twiddle_m(n, b, modified_matrix), x, code)
        vsyms = next_syms(u)
        v1 = tfm_run(v1_tfm, vsyms[:n1+hvec_size_add], u[:n1+hvec_size_add], code, scale_factor)
        v2 = tfm_run(v2_tfm, vsyms[n1+hvec_size_add:], u[n1+hvec_size_add:], code, scale_factor)
        v = np.hstack((v1, v2))
        w = plonka.add_m(n, b, modified_matrix).dot(v)
        return dotx(y, plonka.permute_m(n_orig).T, w, code)
    assert False

def get_code(n, fn):
    global call_num
    call_num = 0
    x = sp.Matrix([sp.Symbol('src[%*d * src_stridea]' % (len(str(n)), i)) for i in range(n)])
    y = sp.Matrix([sp.Symbol('dst[%*d * dst_stridea]' % (len(str(n)), i)) for i in range(n)])
    code = []
    tfm_run(fn, y, x, code)
    indent = 12 * ' '
    outcode = []
    aliases = {}
    for (dst, src) in code:
        dst = str(dst)

        # yeah well...
        src = str(src).replace('1.0*','')

        # a*x + a*y -> a * (x + y)
        # XXX: sympy sucks at refactoring
        s = src.split()
        if len(s) == 3 and s[1] in ('-', '+'):
            a = s[0].split('*')
            b = s[2].split('*')
            if len(a) == 2 and len(b) == 2:
                cst1, xval1 = a
                cst2, xval2 = b
                if cst1.startswith('x'): xval1, cst1 = a
                if cst2.startswith('x'): xval2, cst2 = b
                if cst1 == cst2:
                    src = '%s * (%s %s %s)' % (cst1, xval1, s[1], xval2)

        # a*x + <whatever> + a*y -> a*(x + y) + <whatever>
        # XXX: again sympy sucks... anyone willing to suggest a better solution?
        m = re.match(r'([0-9.-]+)\*(x[0-9a-f]+_[0-9a-f]+x) ([+-] [^+-]*) ([+-]) ([0-9.-]+)\*(x[0-9a-f]+_[0-9a-f]+x)', src)
        if m:
            cst1, var1, middle_expr, sign, cst2, var2 = m.groups()
            if cst1 == cst2:
                src = '%s * (%s %s %s) %s' % (cst1 , var1, sign, var2, middle_expr)

        line = '%s = %s;' % (dst, src)
        if '[' not in dst:
            line = 'float ' + line

        # drop no-op lines such as "const float a = b;" with aliases
        if re.match(r'^float x[0-9a-f]+_[0-9a-f]+x = x[0-9a-f]+_[0-9a-f]+x;$', line):
            #outcode.append(indent + '//' + line)
            aliases[dst] = aliases.get(src, src)
            continue

        # apply any aliases
        for var, rep in aliases.items():
            line = line.replace(var, rep)

        # add 'f' suffix to float literals
        line = re.sub(r'(?<![\w.])(\d+\.\d+)(?![\w.])', r'\1f', line)

        line = indent + line
        outcode.append(line)
    ret = '\n'.join(outcode)

    # look for simple indirections (one assignement, one use)
    var_histogram = Counter(re.findall(r'x[0-9a-f]+_[0-9a-f]+x', ret))
    simple_vars = [key for key, val in var_histogram.items() if val == 2]

    # when the use of this variable is as simple as a = b, replace with the
    # original value
    for var in simple_vars:
        outcode2 = []
        for line in outcode:
            if ' = %s;' % var in line:
                for line2 in outcode:
                    if var in line2:
                        data = line2.split('=')[1]
                        break
                dst, src = line.split('=')
                line = dst + '=' + data
            outcode2.append(line)
        outcode = outcode2
    ret = '\n'.join(outcode)

    # now that the indirection is removed, remove the original assignment which
    # is now unused
    var_histogram = Counter(re.findall(r'x[0-9a-f]+_[0-9a-f]+x', ret))
    orphan_vars = [key for key, val in var_histogram.items() if val == 1]
    for orphan in orphan_vars:
        outcode = [line for line in outcode if orphan not in line]
    ret = '\n'.join(outcode)

    # symbol indexing and renaming
    varsfrom = sorted(set(re.findall(r'x[0-9a-f]+_[0-9a-f]+x', ret)))
    nb_var = len(varsfrom)
    varsto = ['x%0*x' % (len('%x' % nb_var), x) for x in range(nb_var)]
    for var_from, var_to in zip(varsfrom, varsto):
        ret = ret.replace(var_from, var_to)

    return ret

def write_dct_code(n):
    outsrc = open('template.cs').read() #% tpldata
    outsrc = outsrc.replace('%N%', str(n))
    fdct = get_code(n, 'cosII')
    idct = get_code(n, 'cosIII')
    outsrc = outsrc.replace('%CODE_FDCT%', fdct)
    outsrc = outsrc.replace('%CODE_IDCT%', idct)
    if not os.path.exists('gen/cs'):
        os.makedirs('gen/cs')
    if not os.path.exists('refs'):
        os.makedirs('refs')
    open('gen/cs/Dct%d.cs' % n, 'w').write(outsrc)
    open('refs/fdct%d' % n, 'w').write(fdct)
    open('refs/idct%d' % n, 'w').write(idct)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage: {} <N>'.format(sys.argv[0]))
        sys.exit(0)
    write_dct_code(1<<int(sys.argv[1]))