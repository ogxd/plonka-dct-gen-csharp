#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/********* generated code snippet *********/

#define N 2

static inline void fdct_1d(float *dst, const float *src,
                           int dst_stridea, int dst_strideb,
                           int src_stridea, int src_strideb)
{
    int i;

    for (i = 0; i < N; i++) {
        dst[0*dst_stridea] = 0.707106781186547*src[0*src_stridea] + 0.707106781186547*src[1*src_stridea];
        dst[1*dst_stridea] = 0.707106781186547*src[0*src_stridea] - 0.707106781186547*src[1*src_stridea];
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
        dst[0*dst_stridea] = 0.707106781186547*src[0*src_stridea] + 0.707106781186547*src[1*src_stridea];
        dst[1*dst_stridea] = 0.707106781186547*src[0*src_stridea] - 0.707106781186547*src[1*src_stridea];
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
