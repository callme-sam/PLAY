#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

#if 1

/* 16494 */
static int linalg_lu_solve_spatz_serial(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    const float ZERO_f = 0.0f;

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
            asm volatile ("vfmv.v.f v16, %0" :: "f"(ZERO_f));
            asm volatile ("vfmv.v.f v24, %0" :: "f"(ZERO_f));

            for (; avl > 0; avl -= vl) {
                asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

                asm volatile ("vle32.v v0, (%0)" :: "r"(p_mat));
                asm volatile ("vle32.v v8, (%0)" :: "r"(p_y));

                asm volatile ("vfmacc.vv v16, v0, v8");

                p_mat += vl;
                p_y += vl;
            }

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile ("vfredsum.vs v24, v16, v24");

            asm volatile ("vfmv.f.s %0, v24" : "=f"(sum));
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
            asm volatile ("vfmv.v.f v16, %0" :: "f"(ZERO_f));
            asm volatile ("vfmv.v.f v24, %0" :: "f"(ZERO_f));

            for (; avl > 0; avl -= vl) {
                asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

                asm volatile ("vle32.v v8, (%0)" :: "r"(p_result));
                asm volatile ("vle32.v v0, (%0)" :: "r"(p_mat));
                snrt_cluster_hw_barrier();

                asm volatile ("vfmacc.vv v16, v0, v8");

                p_result += vl;
                p_mat += vl;
            }

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile ("vfredsum.vs v24, v16, v24");

            asm volatile ("vfmv.f.s %0, v24" : "=f"(sum));
        }

        result[m] = (y[m] - sum) / mat[m * dim_N + m];
    }

    return 0;
}

#else

#if 0
/* 17363 */
static int linalg_lu_solve_spatz_serial(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    const float ZERO_f = 0.0f;

    size_t original_avl;
    size_t avl2;
    size_t avl1;
    size_t vl;

    const float *p_mat;
    float *p_result;
    float *p_y;
    float *y;

    int perm_idx;
    float sum;

    y = snrt_l1alloc(dim_M * sizeof(float));

    for (int m = 0; m < dim_M; m++) {
        p_mat = mat + m * dim_N;
        p_y   = y;

        original_avl = m;
        avl1 = m;

        perm_idx = perm[m];
        sum = ZERO_f;

        if (m != 0) {
            asm volatile ("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl1));
            asm volatile ("vfmv.v.f v16, %0" :: "f"(ZERO_f));
            asm volatile ("vfmv.v.f v20, %0" :: "f"(ZERO_f));
            asm volatile ("vfmv.v.f v24, %0" :: "f"(ZERO_f));

            for (; avl1 > 0; avl1 -= (vl << 1)) {

                asm volatile("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl1));

                asm volatile("vle32.v v0, (%0)" :: "r"(p_mat));
                asm volatile("vle32.v v8, (%0)" :: "r"(p_y));

                asm volatile("vfmacc.vv v16, v0, v8");

                p_mat += vl;
                p_y   += vl;

                avl2 = avl1 - vl;
                if (avl2 <= 0)
                    break;

                asm volatile("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl2));

                asm volatile("vle32.v v4, (%0)" :: "r"(p_mat));
                asm volatile("vle32.v v12, (%0)" :: "r"(p_y));

                asm volatile("vfmacc.vv v20, v4, v12");

                p_mat += vl;
                p_y   += vl;
            }

            asm volatile("vfadd.vv v16, v16, v20");

            asm volatile("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile("vfredsum.vs v24, v16, v24");

            asm volatile("vfmv.f.s %0, v24" : "=f"(sum));
        }

        y[m] = vec[perm_idx] - sum;
    }


    for (int m = dim_M - 1; m >= 0; m--) {
        p_mat = mat + m * dim_N + (m + 1);
        p_result = result + (m + 1);

        original_avl = dim_N - (m + 1);
        avl1 = original_avl;

        sum = ZERO_f;

        if (avl1 != 0) {

            asm volatile("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl1));

            asm volatile("vfmv.v.f v16, %0" :: "f"(ZERO_f));
            asm volatile("vfmv.v.f v20, %0" :: "f"(ZERO_f));
            asm volatile("vfmv.v.f v24, %0" :: "f"(ZERO_f));


            for (; avl1 > 0; avl1 -= (vl << 1)) {

                asm volatile("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl1));

                asm volatile("vle32.v v0, (%0)" :: "r"(p_mat));
                asm volatile("vle32.v v8, (%0)" :: "r"(p_result));
                snrt_cluster_hw_barrier();

                asm volatile("vfmacc.vv v16, v0, v8");

                p_mat    += vl;
                p_result += vl;

                size_t avl2 = avl1 - vl;
                if (avl2 <= 0)
                    break;

                asm volatile("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl2));

                asm volatile("vle32.v v4, (%0)" :: "r"(p_mat));
                asm volatile("vle32.v v12, (%0)" :: "r"(p_result));
                snrt_cluster_hw_barrier();

                asm volatile("vfmacc.vv v20, v4, v12");

                p_mat    += vl;
                p_result += vl;
            }

            asm volatile("vfadd.vv v16, v16, v20");

            asm volatile("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile("vfredsum.vs v24, v16, v24");

            asm volatile("vfmv.f.s %0, v24" : "=f"(sum));
        }

        result[m] = (y[m] - sum) / mat[m * dim_N + m];
    }

    return 0;
}

#else

/* 18313 */
static int linalg_lu_solve_spatz_serial(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    const float ZERO_f = 0.0f;

    size_t original_avl;
    size_t avl;
    size_t vl;

    const float *p_mat;
    float *p_result;
    float *p_y;
    float *y;

    int processed;
    int perm_idx;
    float sum;

    y = snrt_l1alloc(dim_M * sizeof(float));

    for (int m = 0; m < dim_M; m++) {
        p_mat = mat + m * dim_N;
        p_y   = y;

        original_avl = m;
        avl = m;

        perm_idx = perm[m];
        sum = ZERO_f;

        if (m != 0) {
            asm volatile ("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl));
            asm volatile ("vfmv.v.f v16, %0" :: "f"(ZERO_f));
            asm volatile ("vfmv.v.f v20, %0" :: "f"(ZERO_f));
            asm volatile ("vfmv.v.f v24, %0" :: "f"(ZERO_f));

            for (processed = 0; processed < (int)((int)original_avl - (vl * 2)); processed += (vl * 2)) {
                asm volatile ("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl));

                asm volatile ("vle32.v v0, (%0)" :: "r"(p_mat));
                asm volatile ("vle32.v v4, (%0)" :: "r"(p_y));

                asm volatile ("vle32.v v8, (%0)" :: "r"(p_mat + vl));
                asm volatile ("vle32.v v12, (%0)" :: "r"(p_y + vl));

                asm volatile ("vfmacc.vv v16, v0, v4");
                asm volatile ("vfmacc.vv v20, v8, v12");

                p_mat += (vl * 2);
                p_y += (vl * 2);
                avl = original_avl - processed;
            }

            if (processed < (int)original_avl) {
                for (; avl > 0; avl -= vl) {
                    asm volatile ("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl));

                    asm volatile ("vle32.v v0, (%0)" :: "r"(p_mat));
                    asm volatile ("vle32.v v4, (%0)" :: "r"(p_y));

                    asm volatile ("vfmacc.vv v16, v0, v4");

                    p_mat += vl;
                    p_y += vl;
                }
            }

            asm volatile ("vfadd.vv v28, v16, v20");

            asm volatile ("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile ("vfredsum.vs v24, v28, v24");

            asm volatile ("vfmv.f.s %0, v24" : "=f"(sum));
        }

        y[m] = vec[perm_idx] - sum;
    }


    for (int m = dim_M - 1; m >= 0; m--) {
        p_mat = mat + m * dim_N + (m + 1);
        p_result = result + (m + 1);

        original_avl = dim_N - (m + 1);
        avl = original_avl;

        sum = ZERO_f;

        if (avl != 0) {
            asm volatile("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl));
            asm volatile("vfmv.v.f v16, %0" :: "f"(ZERO_f));
            asm volatile("vfmv.v.f v20, %0" :: "f"(ZERO_f));
            asm volatile("vfmv.v.f v24, %0" :: "f"(ZERO_f));


            for (processed = 0; processed < (int)((int)original_avl - (vl * 2)); processed += (vl * 2)) {
                asm volatile("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl));

                asm volatile ("vle32.v v0, (%0)" :: "r"(p_mat));
                asm volatile ("vle32.v v4, (%0)" :: "r"(p_result));

                asm volatile ("vle32.v v8, (%0)" :: "r"(p_mat + vl));
                asm volatile ("vle32.v v12, (%0)" :: "r"(p_result + vl));
                snrt_cluster_hw_barrier();

                asm volatile("vfmacc.vv v16, v0, v4");
                asm volatile("vfmacc.vv v20, v8, v12");

                p_mat    += (vl * 2);
                p_result += (vl * 2);
                avl = original_avl - processed;
            }

            if (processed < (int)original_avl) {
                for (; avl > 0; avl -= vl) {
                    asm volatile ("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl));

                    asm volatile ("vle32.v v0, (%0)" :: "r"(p_mat));
                    asm volatile ("vle32.v v4, (%0)" :: "r"(p_result));
                    snrt_cluster_hw_barrier();

                    asm volatile ("vfmacc.vv v16, v0, v4");

                    p_mat += vl;
                    p_result += vl;
                }
            }

            asm volatile("vfadd.vv v28, v16, v20");

            asm volatile("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile("vfredsum.vs v24, v28, v24");

            asm volatile("vfmv.f.s %0, v24" : "=f"(sum));
        }

        result[m] = (y[m] - sum) / mat[m * dim_N + m];
    }

    return 0;
}
#endif
#endif

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
