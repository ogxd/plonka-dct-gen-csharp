#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/********* generated code snippet *********/

#define N 16

static inline void fdct_1d(float *dst, const float *src,
                           int dst_stridea, int dst_strideb,
                           int src_stridea, int src_strideb)
{
    int i;

    for (i = 0; i < N; i++) {
        const float x00 = src[ 0*src_stridea] + src[15*src_stridea];
        const float x01 = src[ 1*src_stridea] + src[14*src_stridea];
        const float x02 = src[ 2*src_stridea] + src[13*src_stridea];
        const float x03 = src[ 3*src_stridea] + src[12*src_stridea];
        const float x04 = src[ 4*src_stridea] + src[11*src_stridea];
        const float x05 = src[ 5*src_stridea] + src[10*src_stridea];
        const float x06 = src[ 6*src_stridea] + src[ 9*src_stridea];
        const float x07 = src[ 7*src_stridea] + src[ 8*src_stridea];
        const float x08 = src[ 0*src_stridea] - src[15*src_stridea];
        const float x09 = src[ 1*src_stridea] - src[14*src_stridea];
        const float x0a = src[ 2*src_stridea] - src[13*src_stridea];
        const float x0b = src[ 3*src_stridea] - src[12*src_stridea];
        const float x0c = src[ 4*src_stridea] - src[11*src_stridea];
        const float x0d = src[ 5*src_stridea] - src[10*src_stridea];
        const float x0e = src[ 6*src_stridea] - src[ 9*src_stridea];
        const float x0f = src[ 7*src_stridea] - src[ 8*src_stridea];
        const float x10 = x00 + x07;
        const float x11 = x01 + x06;
        const float x12 = x02 + x05;
        const float x13 = x03 + x04;
        const float x14 = x00 - x07;
        const float x15 = x01 - x06;
        const float x16 = x02 - x05;
        const float x17 = x03 - x04;
        const float x18 = x10 + x13;
        const float x19 = x11 + x12;
        const float x1a = x10 - x13;
        const float x1b = x11 - x12;
        const float x1c = 1.38703984532215*x14 + 0.275899379282943*x17;
        const float x1d = 1.17587560241936*x15 + 0.785694958387102*x16;
        const float x1e = -0.785694958387102*x15 + 1.17587560241936*x16;
        const float x1f = 0.275899379282943*x14 - 1.38703984532215*x17;
        const float x20 = 0.25 * (x1c - x1d);
        const float x21 = 0.25 * (x1e - x1f);
        const float x22 = 1.40740373752638*x08 + 0.138617169199091*x0f;
        const float x23 = 1.35331800117435*x09 + 0.410524527522357*x0e;
        const float x24 = 1.24722501298667*x0a + 0.666655658477747*x0d;
        const float x25 = 1.09320186700176*x0b + 0.897167586342636*x0c;
        const float x26 = -0.897167586342636*x0b + 1.09320186700176*x0c;
        const float x27 = 0.666655658477747*x0a - 1.24722501298667*x0d;
        const float x28 = -0.410524527522357*x09 + 1.35331800117435*x0e;
        const float x29 = 0.138617169199091*x08 - 1.40740373752638*x0f;
        const float x2a = x22 + x25;
        const float x2b = x23 + x24;
        const float x2c = x22 - x25;
        const float x2d = x23 - x24;
        const float x2e = 0.25 * (x2a - x2b);
        const float x2f = 0.326640741219094*x2c + 0.135299025036549*x2d;
        const float x30 = 0.135299025036549*x2c - 0.326640741219094*x2d;
        const float x31 = x26 + x29;
        const float x32 = x27 + x28;
        const float x33 = x26 - x29;
        const float x34 = x27 - x28;
        const float x35 = 0.25 * (x31 - x32);
        const float x36 = 0.326640741219094*x33 + 0.135299025036549*x34;
        const float x37 = 0.135299025036549*x33 - 0.326640741219094*x34;
        dst[ 0*dst_stridea] = 0.25 * (x18 + x19);
        dst[ 1*dst_stridea] = 0.25 * (x2a + x2b);
        dst[ 2*dst_stridea] = 0.25 * (x1c + x1d);
        dst[ 3*dst_stridea] = 0.707106781186547 * (x2f - x37);
        dst[ 4*dst_stridea] = 0.326640741219094*x1a + 0.135299025036549*x1b;
        dst[ 5*dst_stridea] = 0.707106781186547 * (x2f + x37);
        dst[ 6*dst_stridea] = 0.707106781186547 * (x20 - x21);
        dst[ 7*dst_stridea] = 0.707106781186547 * (x2e + x35);
        dst[ 8*dst_stridea] = 0.25 * (x18 - x19);
        dst[ 9*dst_stridea] = 0.707106781186547 * (x2e - x35);
        dst[10*dst_stridea] = 0.707106781186547 * (x20 + x21);
        dst[11*dst_stridea] = 0.707106781186547 * (x30 - x36);
        dst[12*dst_stridea] = 0.135299025036549*x1a - 0.326640741219094*x1b;
        dst[13*dst_stridea] = 0.707106781186547 * (x30 + x36);
        dst[14*dst_stridea] = 0.25 * (x1e + x1f);
        dst[15*dst_stridea] = 0.25 * (x31 + x32);
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
        const float x00 = 1.4142135623731*src[ 0*src_stridea];
        const float x01 = 1.40740373752638*src[ 1*src_stridea] + 0.138617169199091*src[15*src_stridea];
        const float x02 = 1.38703984532215*src[ 2*src_stridea] + 0.275899379282943*src[14*src_stridea];
        const float x03 = 1.35331800117435*src[ 3*src_stridea] + 0.410524527522357*src[13*src_stridea];
        const float x04 = 1.30656296487638*src[ 4*src_stridea] + 0.541196100146197*src[12*src_stridea];
        const float x05 = 1.24722501298667*src[ 5*src_stridea] + 0.666655658477747*src[11*src_stridea];
        const float x06 = 1.17587560241936*src[ 6*src_stridea] + 0.785694958387102*src[10*src_stridea];
        const float x07 = 1.09320186700176*src[ 7*src_stridea] + 0.897167586342636*src[ 9*src_stridea];
        const float x08 = 1.4142135623731*src[ 8*src_stridea];
        const float x09 = -0.897167586342636*src[ 7*src_stridea] + 1.09320186700176*src[ 9*src_stridea];
        const float x0a = 0.785694958387102*src[ 6*src_stridea] - 1.17587560241936*src[10*src_stridea];
        const float x0b = -0.666655658477747*src[ 5*src_stridea] + 1.24722501298667*src[11*src_stridea];
        const float x0c = 0.541196100146197*src[ 4*src_stridea] - 1.30656296487638*src[12*src_stridea];
        const float x0d = -0.410524527522357*src[ 3*src_stridea] + 1.35331800117435*src[13*src_stridea];
        const float x0e = 0.275899379282943*src[ 2*src_stridea] - 1.38703984532215*src[14*src_stridea];
        const float x0f = -0.138617169199091*src[ 1*src_stridea] + 1.40740373752638*src[15*src_stridea];
        const float x12 = x00 + x08;
        const float x13 = x01 + x07;
        const float x14 = x02 + x06;
        const float x15 = x03 + x05;
        const float x16 = 1.4142135623731*x04;
        const float x17 = x00 - x08;
        const float x18 = x01 - x07;
        const float x19 = x02 - x06;
        const float x1a = x03 - x05;
        const float x1d = x12 + x16;
        const float x1e = x13 + x15;
        const float x1f = 1.4142135623731*x14;
        const float x20 = x12 - x16;
        const float x21 = x13 - x15;
        const float x22 = 0.25 * (x1d - x1f);
        const float x23 = 0.25 * (x20 + x21);
        const float x24 = 0.25 * (x20 - x21);
        const float x25 = 1.4142135623731*x17;
        const float x26 = 1.30656296487638*x18 + 0.541196100146197*x1a;
        const float x27 = 1.4142135623731*x19;
        const float x28 = -0.541196100146197*x18 + 1.30656296487638*x1a;
        const float x29 = 0.176776695296637 * (x25 + x27) + 0.25*x26;
        const float x2a = 0.25 * (x25 - x27);
        const float x2b = 0.176776695296637 * (x25 + x27) - 0.25*x26;
        const float x2c = 0.353553390593274*x28;
        const float x1b = 0.707106781186547 * (x2a - x2c);
        const float x1c = 0.707106781186547 * (x2a + x2c);
        const float x2d = 1.4142135623731*x0c;
        const float x2e = x0b + x0d;
        const float x2f = x0a + x0e;
        const float x30 = x09 + x0f;
        const float x31 = x09 - x0f;
        const float x32 = x0a - x0e;
        const float x33 = x0b - x0d;
        const float x37 = 1.4142135623731*x2d;
        const float x38 = 1.30656296487638*x2e + 0.541196100146197*x30;
        const float x39 = 1.4142135623731*x2f;
        const float x3a = -0.541196100146197*x2e + 1.30656296487638*x30;
        const float x3b = 0.176776695296637 * (x37 + x39) + 0.25*x38;
        const float x3c = 0.25 * (x37 - x39);
        const float x3d = 0.176776695296637 * (x37 + x39) - 0.25*x38;
        const float x3e = 0.353553390593274*x3a;
        const float x34 = 0.707106781186547 * (x3c - x3e);
        const float x35 = 0.707106781186547 * (x3c + x3e);
        const float x3f = 1.4142135623731*x32;
        const float x40 = x31 + x33;
        const float x41 = x31 - x33;
        const float x42 = 0.25 * (x3f + x40);
        const float x43 = 0.25 * (x3f - x40);
        const float x44 = 0.353553390593274*x41;
        const float x36 = -x43;
        const float x10 = -x34;
        const float x11 = -x3d;
        dst[ 0*dst_stridea] = 0.176776695296637 * (x1d + x1f) + 0.25*x1e;
        dst[ 1*dst_stridea] = 0.707106781186547 * (x29 - x11);
        dst[ 2*dst_stridea] = 0.707106781186547 * (x29 + x11);
        dst[ 3*dst_stridea] = 0.707106781186547 * (x23 + x36);
        dst[ 4*dst_stridea] = 0.707106781186547 * (x23 - x36);
        dst[ 5*dst_stridea] = 0.707106781186547 * (x1b - x35);
        dst[ 6*dst_stridea] = 0.707106781186547 * (x1b + x35);
        dst[ 7*dst_stridea] = 0.707106781186547 * (x22 + x44);
        dst[ 8*dst_stridea] = 0.707106781186547 * (x22 - x44);
        dst[ 9*dst_stridea] = 0.707106781186547 * (x1c - x10);
        dst[10*dst_stridea] = 0.707106781186547 * (x1c + x10);
        dst[11*dst_stridea] = 0.707106781186547 * (x24 + x42);
        dst[12*dst_stridea] = 0.707106781186547 * (x24 - x42);
        dst[13*dst_stridea] = 0.707106781186547 * (x2b - x3b);
        dst[14*dst_stridea] = 0.707106781186547 * (x2b + x3b);
        dst[15*dst_stridea] = 0.176776695296637 * (x1d + x1f) - 0.25*x1e;
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
