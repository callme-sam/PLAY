#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"
#include "printf.h" // TODO: remove

static int linalg_lu_solve_spatz_serial(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    size_t original_avl;
    size_t avl;
    size_t vl;

    const float *p_mat;
    float *p_result;
    float *p_y;
    float *y;

    int perm_idx;
    float sum;

    y = snrt_l1alloc(dim_M * sizeof(float));

    /* Forward substitution (L * y = perm * v) */
    for (int m = 0; m < dim_M; m++) {
        p_mat = mat + m * dim_N;
        p_y = y;

        original_avl = m;
        avl = m;

        perm_idx = perm[m];
        sum = 0;

        if (m != 0) {
            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
            asm volatile ("vfmv.v.f v16, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v24, %0" :: "f"(0.0f));
            // snrt_cluster_hw_barrier();

            for (; avl > 0; avl -= vl) {
                asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

                asm volatile ("vle32.v v0, (%0)" :: "r"(p_mat));
                asm volatile ("vle32.v v8, (%0)" :: "r"(p_y));
                snrt_cluster_hw_barrier();

                asm volatile ("vfmacc.vv v16, v0, v8");
                snrt_cluster_hw_barrier();

                p_mat += vl;
                p_y += vl;
            }

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile ("vfredsum.vs v24, v16, v24");
            snrt_cluster_hw_barrier();

            asm volatile ("vfmv.f.s %0, v24" : "=f"(sum));
            snrt_cluster_hw_barrier();
        }

        y[m] = vec[perm_idx] - sum;
    }

    for (int m = (dim_M - 1); m >= 0; m--) {
        p_mat = mat + m * dim_N + (m + 1);
        p_result = result + (m + 1);

        original_avl = dim_N - (m + 1);
        avl = original_avl;

        sum = 0;

        if (avl != 0) {
            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
            asm volatile ("vfmv.v.f v16, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v24, %0" :: "f"(0.0f));
            // snrt_cluster_hw_barrier();

            for (; avl > 0; avl -= vl) {
                asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

                asm volatile ("vle32.v v8, (%0)" :: "r"(p_result));
                asm volatile ("vle32.v v0, (%0)" :: "r"(p_mat));
                snrt_cluster_hw_barrier();

                asm volatile ("vfmacc.vv v16, v0, v8");
                snrt_cluster_hw_barrier();

                p_result += vl;
                p_mat += vl;
            }

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile ("vfredsum.vs v24, v16, v24");
            snrt_cluster_hw_barrier();

            asm volatile ("vfmv.f.s %0, v24" : "=f"(sum));
            snrt_cluster_hw_barrier();
        }

        result[m] = (y[m] - sum) / mat[m * dim_N + m];
        snrt_cluster_hw_barrier();
    }

    return 0;
}

__attribute__((noinline)) int linalg_lu_solve_impl(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    #error "Parallel execution on SPATZ not supported yet"
#else   /* CLUSTER */
    ret = linalg_lu_solve_spatz_serial(mat, vec, perm, result, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
