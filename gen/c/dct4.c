#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/********* generated code snippet *********/

#define N 4

static inline void fdct_1d(float *dst, const float *src,
                           int dst_stridea, int dst_strideb,
                           int src_stridea, int src_strideb)
{
    int i;

    for (i = 0; i < N; i++) {
        const float x0 = src[0*src_stridea] + src[3*src_stridea];
        const float x1 = src[1*src_stridea] + src[2*src_stridea];
        const float x2 = src[0*src_stridea] - src[3*src_stridea];
        const float x3 = src[1*src_stridea] - src[2*src_stridea];
        dst[0*dst_stridea] = 0.5 * (x0 + x1);
        dst[1*dst_stridea] = 0.653281482438188*x2 + 0.270598050073099*x3;
        dst[2*dst_stridea] = 0.5 * (x0 - x1);
        dst[3*dst_stridea] = 0.270598050073099*x2 - 0.653281482438188*x3;
        dst += dst_strideb;
        src += src_strideb;
    }
}

static void fdct(float *dst, const float *src)
{
    float tmp[N*N];
    fdct_1d(tmp, src, 1, N, 1, N);
    fdct_1d(dst, tmp, N, 1, N, 1);
}

static inline void idct_1d(float *dst, const float *src,
                           int dst_stridea, int dst_strideb,
                           int src_stridea, int src_strideb)
{
    int i;

    for (i = 0; i < N; i++) {
        const float x0 = 1.4142135623731*src[0*src_stridea];
        const float x1 = 1.30656296487638*src[1*src_stridea] + 0.541196100146197*src[3*src_stridea];
        const float x2 = 1.4142135623731*src[2*src_stridea];
        const float x3 = -0.541196100146197*src[1*src_stridea] + 1.30656296487638*src[3*src_stridea];
        const float x4 = 0.5 * (x0 - x2);
        const float x5 = 0.707106781186547*x3;
        dst[0*dst_stridea] = 0.353553390593274 * (x0 + x2) + 0.5*x1;
        dst[1*dst_stridea] = 0.707106781186547 * (x4 - x5);
        dst[2*dst_stridea] = 0.707106781186547 * (x4 + x5);
        dst[3*dst_stridea] = 0.353553390593274 * (x0 + x2) - 0.5*x1;
        dst += dst_strideb;
        src += src_strideb;
    }
}

static void idct(float *dst, const float *src)
{
    float tmp[N*N];
    idct_1d(tmp, src, 1, N, 1, N);
    idct_1d(dst, tmp, N, 1, N, 1);
}
