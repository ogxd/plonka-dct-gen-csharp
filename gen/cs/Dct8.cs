using System.Runtime.CompilerServices;

namespace PlonkaDct;

public static unsafe class Dct8 {

    private const int N = 8;

    public static void ForwardDct(ReadOnlySpan<float> source, Span<float> destination)
    {
        fixed (float* dst = destination)
        fixed (float* src = source)
        {
            float* tmp = stackalloc float[N*N];
            ForwardDct1d(tmp, src, 1, N, 1, N);
            ForwardDct1d(dst, tmp, N, 1, N, 1);
        }
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    private static void ForwardDct1d(
        float* dst, float* src,
        int dst_stridea, int dst_strideb,
        int src_stridea, int src_strideb)
    {
        int i;

        for (i = 0; i < N; i++) {
            float x00 = src[0 * src_stridea] + src[7 * src_stridea];
            float x01 = src[1 * src_stridea] + src[6 * src_stridea];
            float x02 = src[2 * src_stridea] + src[5 * src_stridea];
            float x03 = src[3 * src_stridea] + src[4 * src_stridea];
            float x04 = src[0 * src_stridea] - src[7 * src_stridea];
            float x05 = src[1 * src_stridea] - src[6 * src_stridea];
            float x06 = src[2 * src_stridea] - src[5 * src_stridea];
            float x07 = src[3 * src_stridea] - src[4 * src_stridea];
            float x08 = x00 + x03;
            float x09 = x01 + x02;
            float x0a = x00 - x03;
            float x0b = x01 - x02;
            float x0c = 1.38703984532215f*x04 + 0.275899379282943f*x07;
            float x0d = 1.17587560241936f*x05 + 0.785694958387102f*x06;
            float x0e = -0.785694958387102f*x05 + 1.17587560241936f*x06;
            float x0f = 0.275899379282943f*x04 - 1.38703984532215f*x07;
            float x10 = 0.353553390593274f * (x0c - x0d);
            float x11 = 0.353553390593274f * (x0e - x0f);
            dst[0 * dst_stridea] = 0.353553390593274f * (x08 + x09);
            dst[1 * dst_stridea] = 0.353553390593274f * (x0c + x0d);
            dst[2 * dst_stridea] = 0.461939766255643f*x0a + 0.191341716182545f*x0b;
            dst[3 * dst_stridea] = 0.707106781186547f * (x10 - x11);
            dst[4 * dst_stridea] = 0.353553390593274f * (x08 - x09);
            dst[5 * dst_stridea] = 0.707106781186547f * (x10 + x11);
            dst[6 * dst_stridea] = 0.191341716182545f*x0a - 0.461939766255643f*x0b;
            dst[7 * dst_stridea] = 0.353553390593274f * (x0e + x0f);
            dst += dst_strideb;
            src += src_strideb;
        }
    }

    public static void InverseDct(ReadOnlySpan<float> source, Span<float> destination)
    {
        fixed (float* dst = destination)
        fixed (float* src = source)
        {
            float* tmp = stackalloc float[N*N];
            InverseDct1d(tmp, src, 1, N, 1, N);
            InverseDct1d(dst, tmp, N, 1, N, 1);
        }
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    private static void InverseDct1d(
        float* dst, float* src,
        int dst_stridea, int dst_strideb,
        int src_stridea, int src_strideb)
    {
        int i;

        for (i = 0; i < N; i++) {
            float x00 = 1.4142135623731f*src[0 * src_stridea];
            float x01 = 1.38703984532215f*src[1 * src_stridea] + 0.275899379282943f*src[7 * src_stridea];
            float x02 = 1.30656296487638f*src[2 * src_stridea] + 0.541196100146197f*src[6 * src_stridea];
            float x03 = 1.17587560241936f*src[3 * src_stridea] + 0.785694958387102f*src[5 * src_stridea];
            float x04 = 1.4142135623731f*src[4 * src_stridea];
            float x05 = -0.785694958387102f*src[3 * src_stridea] + 1.17587560241936f*src[5 * src_stridea];
            float x06 = 0.541196100146197f*src[2 * src_stridea] - 1.30656296487638f*src[6 * src_stridea];
            float x07 = -0.275899379282943f*src[1 * src_stridea] + 1.38703984532215f*src[7 * src_stridea];
            float x09 = x00 + x04;
            float x0a = x01 + x03;
            float x0b = 1.4142135623731f*x02;
            float x0c = x00 - x04;
            float x0d = x01 - x03;
            float x0e = 0.353553390593274f * (x09 - x0b);
            float x0f = 0.353553390593274f * (x0c + x0d);
            float x10 = 0.353553390593274f * (x0c - x0d);
            float x11 = 1.4142135623731f*x06;
            float x12 = x05 + x07;
            float x13 = x05 - x07;
            float x14 = 0.353553390593274f * (x11 + x12);
            float x15 = 0.353553390593274f * (x11 - x12);
            float x16 = 0.5f*x13;
            float x08 = -x15;
            dst[0 * dst_stridea] = 0.25f * (x09 + x0b) + 0.353553390593274f*x0a;
            dst[1 * dst_stridea] = 0.707106781186547f * (x0f - x08);
            dst[2 * dst_stridea] = 0.707106781186547f * (x0f + x08);
            dst[3 * dst_stridea] = 0.707106781186547f * (x0e + x16);
            dst[4 * dst_stridea] = 0.707106781186547f * (x0e - x16);
            dst[5 * dst_stridea] = 0.707106781186547f * (x10 - x14);
            dst[6 * dst_stridea] = 0.707106781186547f * (x10 + x14);
            dst[7 * dst_stridea] = 0.25f * (x09 + x0b) - 0.353553390593274f*x0a;
            dst += dst_strideb;
            src += src_strideb;
        }
    }
}