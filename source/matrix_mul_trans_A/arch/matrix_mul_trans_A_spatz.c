#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int matrix_mul_trans_A_spatz_serial(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t original_avl;
    size_t stride_a;
    size_t stride_b;
    size_t avl;
    size_t vl;

    const float *row_a_t;
    const float *col_b;

    float sum;

    stride_a = dim_N * sizeof(float);
    stride_b = dim_P * sizeof(float);
    original_avl = dim_M;

    for (int n = 0; n < dim_N; n++) {
        for (int p = 0; p < dim_P; p++) {
            row_a_t = src_a + n;
            col_b = src_b + p;
            avl = dim_M;
            sum = 0;

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0));
            asm volatile ("vfmv.v.f v24, %0" :: "f"(0.0));

            for (; avl > 0; avl -= vl) {
                asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

                asm volatile ("vlse32.v v8, (%0), %1" :: "r"(row_a_t), "r"(stride_a));
                asm volatile ("vlse32.v v16, (%0), %1" :: "r"(col_b), "r"(stride_b));
                snrt_cluster_hw_barrier();

                asm volatile ("vfmacc.vv v0, v8, v16");

                row_a_t += vl * dim_N;
                col_b += vl * dim_P;
            }

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile ("vfredusum.vs v24, v0, v24");
            asm volatile ("vfmv.f.s %0, v24" : "=f"(sum));
            snrt_cluster_hw_barrier();

            dst[n * dim_P + p] = sum;
        }
    }

    return 0;
}

int matrix_mul_trans_A_impl(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not implemented yet"
#else
    ret = matrix_mul_trans_A_spatz_serial(src_a, src_b, dst, dim_M, dim_N, dim_P);
#endif

    return ret;
}
