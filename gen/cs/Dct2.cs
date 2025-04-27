using System.Runtime.CompilerServices;

namespace PlonkaDct;

public static unsafe class Dct2 {

    private const int N = 2;

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
            dst[0 * dst_stridea] = 0.707106781186547f*src[0 * src_stridea] + 0.707106781186547f*src[1 * src_stridea];
            dst[1 * dst_stridea] = 0.707106781186547f*src[0 * src_stridea] - 0.707106781186547f*src[1 * src_stridea];
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
            dst[0 * dst_stridea] = 0.707106781186547f*src[0 * src_stridea] + 0.707106781186547f*src[1 * src_stridea];
            dst[1 * dst_stridea] = 0.707106781186547f*src[0 * src_stridea] - 0.707106781186547f*src[1 * src_stridea];
            dst += dst_strideb;
            src += src_strideb;
        }
    }
}