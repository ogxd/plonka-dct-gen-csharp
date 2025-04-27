# Plonka DCT

Forked from [https://github.com/ubitux/dct](https://github.com/ubitux/dct).

This fork implements generation of csharp code for various 2D DCTs sizes, following plonka's paper.  
I have no idea how this works, I have simply translated the python code to generate csharp code.  

I have committed the genertated c and csharp code so you don't have to do it.  

Beware, this is untested code.

## Original README

Experiment: trying to implement a generic fast DCT II/III based on "Fast and
numerically stable algorithms for discrete cosine transforms" from Gerlind
Plonka & Manfred Tasche (DOI: 10.1016/j.laa.2004.07.015).

• plonka.py contains the litteral implementation of the algorithms (recursive
  form) presented in the paper.
• gen_c.py generates the unrolled C code to compute forward and inverse
  2D DCTs (DCT-II and DCT-III, scaled, floating point) for several dimensions
  (4x4, 8x8, 16x16, ...) using the maths in plonka.py. The 1D DCTs can be
  extracted from that code as well.

Running ``make'' will test the mathematics in plonka.py (test-plonka-*),
generates the C (including tests) for a few DCT (in dct*.c), compile them, and
run them as a test.
