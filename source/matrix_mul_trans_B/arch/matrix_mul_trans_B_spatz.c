#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int matrix_mul_trans_B_spatz_serial(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t original_avl;
    size_t avl;
    size_t vl;

    const float *col_b_t;
    const float *row_a;

    float sum;

    original_avl = dim_N;

    for (int m = 0; m < dim_M; m++) {
        for (int p = 0; p < dim_P; p++) {
            col_b_t = src_b + (p * dim_N);
            row_a = src_a + (m * dim_N);
            avl = dim_N;
            sum = 0;

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0));
            asm volatile ("vfmv.v.f v24, %0" :: "f"(0.0));

            for (; avl > 0; avl -= vl) {
                asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

                asm volatile ("vle32.v v8, (%0)" :: "r"(row_a));
                asm volatile ("vle32.v v16, (%0)" :: "r"(col_b_t));
                snrt_cluster_hw_barrier();

                asm volatile ("vfmacc.vv v0, v8, v16");

                col_b_t += vl;
                row_a += vl;
            }

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile ("vfredusum.vs v24, v0, v24");
            asm volatile ("vfmv.f.s %0, v24" : "=f"(sum));
            snrt_cluster_hw_barrier();

            dst[m * dim_P + p] = sum;
        }
    }

    return 0;
}

int matrix_mul_trans_B_impl(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not implemented yet"
#else
    ret = matrix_mul_trans_B_spatz_serial(src_a, src_b, dst, dim_M, dim_N, dim_P);
#endif

    return ret;
}
