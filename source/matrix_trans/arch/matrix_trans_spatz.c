#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

#if 0

/* 1460 cycl - stride on load */
static int matrix_trans_spatz_serial(const float *src, float *dst, const int dim_M, const int dim_N)
{
    size_t stride;
    size_t avl;
    size_t vl;

    const float *col_src;
    const float *row_dst;

    stride = dim_N * sizeof(float);

    for (int n = 0; n < dim_N; n++) {
        avl = dim_M;
        col_src = src + n;
        row_dst = dst + (n * dim_M);

        for (; avl > 0; avl -= vl) {
            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
            asm volatile ("vlse32.v v0, (%0), %1" :: "r"(col_src), "r"(stride));
            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst));

            col_src += (vl * dim_N);
            row_dst += vl;
        }
    }

    return 0;
}

#else

/* 1392 - stride on store */
static int matrix_trans_spatz_serial(const float *src, float *dst, const int dim_M, const int dim_N)
{
    size_t stride;
    size_t avl;
    size_t vl;

    const float *row_src;
    const float *col_dst;

    stride = dim_M * sizeof(float);

    for (int m = 0; m < dim_M; m++) {
        row_src = src + (m * dim_N);
        col_dst = dst + m;
        avl = dim_N;

        for (; avl > 0; avl -= vl) {
            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
            asm volatile ("vle32.v v0, (%0)" :: "r"(row_src));
            asm volatile ("vsse32.v v0, (%0), %1" :: "r"(col_dst), "r"(stride));

            row_src += vl;
            col_dst += vl * dim_M;
        }
    }

    return 0;
}

#endif

int matrix_trans_impl(const float *src, float *dst, const int dim_M, const int dim_N)
{
    int ret;

#if NUM_CC > 1
    #error "Parralel execution on SPATZ not supported yet"
#else
    ret = matrix_trans_spatz_serial(src, dst, dim_M, dim_N);
#endif

    return ret;
}
