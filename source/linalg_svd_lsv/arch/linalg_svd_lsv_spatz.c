#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

int linalg_svd_lsv_pulp_open_spatz_serial(const float *src, float *mat_V, float *vec_S, float *dst, const int dim_M, const int dim_N)
{
    float ZERO_f = 0.0f;

    const float *row_a1;
    const float *row_a1_next;
    const float *row_a2;
    const float *row_a2_next;
    const float *row_v1;
    const float *row_v1_next;
    const float *p_vec_s;
    float *row_dst1;
    float *row_dst2;

    size_t avl;
    size_t vl;

    for (int k = 0; k < dim_N; k += vl) {
        avl = dim_N - k;
        p_vec_s = vec_S + k;

        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        for (int m = 0; m < (dim_M - 1); m += 2) {
            row_dst1 = dst + (m * dim_N + k);
            row_dst2 = dst + ((m + 1) * dim_N + k);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(ZERO_f));
            asm volatile ("vfmv.v.f v8, %0" :: "f"(ZERO_f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src + (m * dim_N + n);
                row_v1 = mat_V + (n * dim_N + k);
                row_a2 = src + ((m + 1) * dim_N + n);

                row_a1_next = src + (m * dim_N + (n + 1));
                row_a2_next = src + ((m + 1) * dim_N + (n + 1));
                row_v1_next = mat_V + ((n + 1) * dim_N + k);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_v1));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a2));

                asm volatile ("vle32.v v24, (%0)" :: "r"(row_v1_next));
                asm volatile ("vfmacc.vf v0, %0, v24" :: "f"(*row_a1_next));
                asm volatile ("vfmacc.vf v8, %0, v24" :: "f"(*row_a2_next));
            }

            if (dim_N % 2) {
                row_a1 = src + (m * dim_N + (dim_N - 1));
                row_v1 = mat_V + ((dim_N - 1) * dim_N + k);
                row_a2 = src + ((m + 1) * dim_N + (dim_N - 1));

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_v1));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a2));
            }

            /* WARNING: do not use v24 untill the end of the loop on k */
            asm volatile ("vle32.v v24, (%0)" :: "r"(p_vec_s));
            asm volatile ("vfdiv.vv v0, v0, v24");
            asm volatile ("vfdiv.vv v8, v8, v24");

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
            asm volatile ("vse32.v v8, (%0)" :: "r"(row_dst2));
        }

        if (dim_M % 2) {
            row_dst1 = dst + ((dim_M - 1) * dim_N + k);
            asm volatile ("vfmv.v.f v0, %0" :: "f"(ZERO_f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src + ((dim_M - 1) * dim_N + n);
                row_v1 = mat_V + (n * dim_N + k);

                row_a1_next = src + ((dim_M - 1) * dim_N + (n + 1));
                row_v1_next = mat_V + ((n + 1) * dim_N + k);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_v1));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));

                asm volatile ("vle32.v v8, (%0)" :: "r"(row_v1_next));
                asm volatile ("vfmacc.vf v0, %0, v8" :: "f"(*row_a1_next));
            }

            if (dim_N % 2) {
                row_a1 = src + ((dim_M - 1) * dim_N + (dim_N - 1));
                row_v1 = mat_V + ((dim_N - 1) * dim_N + k);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_v1));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
            }

            /* After this division v24 can be used again */
            asm volatile ("vfdiv.vv v0, v0, v24");
            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
        }
    }

    return 0;
}

int linalg_svd_lsv_impl(const float *src, float *mat_V, float *vec_S, float *dst, const int dim_M, const int dim_N)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = linalg_svd_lsv_pulp_open_spatz_serial(src, mat_V, vec_S, dst, dim_M, dim_N);
#endif

    return ret;
}
