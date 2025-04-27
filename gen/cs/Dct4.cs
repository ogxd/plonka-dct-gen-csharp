using System.Runtime.CompilerServices;

namespace PlonkaDct;

public static unsafe class Dct4 {

    private const int N = 4;

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
            float x0 = src[0 * src_stridea] + src[3 * src_stridea];
            float x1 = src[1 * src_stridea] + src[2 * src_stridea];
            float x2 = src[0 * src_stridea] - src[3 * src_stridea];
            float x3 = src[1 * src_stridea] - src[2 * src_stridea];
            dst[0 * dst_stridea] = 0.5f * (x0 + x1);
            dst[1 * dst_stridea] = 0.653281482438188f*x2 + 0.270598050073099f*x3;
            dst[2 * dst_stridea] = 0.5f * (x0 - x1);
            dst[3 * dst_stridea] = 0.270598050073099f*x2 - 0.653281482438188f*x3;
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
            float x0 = 1.4142135623731f*src[0 * src_stridea];
            float x1 = 1.30656296487638f*src[1 * src_stridea] + 0.541196100146197f*src[3 * src_stridea];
            float x2 = 1.4142135623731f*src[2 * src_stridea];
            float x3 = -0.541196100146197f*src[1 * src_stridea] + 1.30656296487638f*src[3 * src_stridea];
            float x4 = 0.5f * (x0 - x2);
            float x5 = 0.707106781186547f*x3;
            dst[0 * dst_stridea] = 0.353553390593274f * (x0 + x2) + 0.5f*x1;
            dst[1 * dst_stridea] = 0.707106781186547f * (x4 - x5);
            dst[2 * dst_stridea] = 0.707106781186547f * (x4 + x5);
            dst[3 * dst_stridea] = 0.353553390593274f * (x0 + x2) - 0.5f*x1;
            dst += dst_strideb;
            src += src_strideb;
        }
    }
}