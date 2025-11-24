#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int matrix_mul_trans_B_spatz_serial(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t stride;
    size_t avl;
    size_t vl;

    const float *row_a1;
    const float *row_a1_next;
    const float *row_a2;
    const float *row_a2_next;
    const float *col_b1;        /* i.e. i-th row of B^t             */
    const float *col_b1_next;   /* i.2. i-th row, next elem, of B^t */
    float *row_dst1;
    float *row_dst2;

    stride = dim_N * sizeof(float);

    for (int p = 0; p < dim_P; p += vl) {
        avl = dim_P - p;
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        for (int m = 0; m < (dim_M - 1); m += 2) {
            row_dst1 = dst + (m * dim_P + p);
            row_dst2 = dst + ((m + 1) * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v8, %0" :: "f"(0.0f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src_a + (m * dim_N + n);
                row_a2 = src_a + ((m + 1) * dim_N + n);

                row_a1_next = src_a + (m * dim_N + (n + 1));
                row_a2_next = src_a + ((m + 1) * dim_N + (n + 1));

                col_b1 = src_b + (p * dim_N + n);
                col_b1_next = src_b + (p * dim_N + (n + 1));

                asm volatile ("vlse32.v v16, (%0), %1" :: "r"(col_b1), "r"(stride));
                snrt_cluster_hw_barrier();
                asm volatile ("vlse32.v v24, (%0), %1" :: "r"(col_b1_next), "r"(stride));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a2));

                snrt_cluster_hw_barrier();
                asm volatile ("vfmacc.vf v0, %0, v24" :: "f"(*row_a1_next));
                asm volatile ("vfmacc.vf v8, %0, v24" :: "f"(*row_a2_next));
            }

            if (dim_N % 2) {
                row_a1 = src_a + (m * dim_N + (dim_N - 1));
                row_a2 = src_a + ((m + 1) * dim_N + (dim_N - 1));
                col_b1 = src_b + (p * dim_N + (dim_N - 1));

                asm volatile ("vlse32.v v16, (%0), %1" :: "r"(col_b1), "r"(stride));
                snrt_cluster_hw_barrier();
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a2));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
            asm volatile ("vse32.v v8, (%0)" :: "r"(row_dst2));
        }

        if (dim_M % 2) {
            row_dst1 = dst + ((dim_M - 1) * dim_P + p);
            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src_a + ((dim_M - 1) * dim_N + n);
                row_a1_next = src_a + ((dim_M - 1) * dim_N + (n + 1));

                col_b1 = src_b + (p * dim_N + n);
                col_b1_next = src_b + (p * dim_N + (n + 1));

                asm volatile ("vlse32.v v16, (%0), %1" :: "r"(col_b1), "r"(stride));
                snrt_cluster_hw_barrier();
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));

                asm volatile ("vlse32.v v24, (%0), %1" :: "r"(col_b1_next), "r"(stride));
                snrt_cluster_hw_barrier();
                asm volatile ("vfmacc.vf v0, %0, v24" :: "f"(*row_a1_next));
            }

            if (dim_N % 2) {
                row_a1 = src_a + ((dim_M - 1) * dim_N + (dim_N - 1));
                col_b1 = src_b + (p * dim_N + (dim_N - 1));

                asm volatile ("vlse32.v v16, (%0), %1" :: "r"(col_b1), "r"(stride));
                snrt_cluster_hw_barrier();
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
        }
    }
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
