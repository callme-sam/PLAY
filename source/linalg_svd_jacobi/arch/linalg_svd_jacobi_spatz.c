#include "internal/arch_interface.h"
#include "play.h"

#include <math.h>

#include "snrt.h"

const float ONE_f = 1;
const float TWO_f = 2;
const int MAX_ITER = 800;
const float EPSILON = 1e-12;

static int matrix_set_identity(float *mat, const int dim_M)
{
    for (int m = 0; m < dim_M; m++)
        mat[m * dim_M + m] = 1.0;

    return 0;
}

static int linalg_svd_jacobi_spatz_serial(float *mat, float *mat_V, float *vec_S, const int dim_M)
{
    int iter;
    float max_offdiag;

    size_t stride;
    size_t avl;
    size_t vl;

    float *row_i;
    float *row_j;
    float *col_i;
    float *col_j;

    matrix_set_identity(mat_V, dim_M);
    stride = dim_M * sizeof(float);

    iter = 0;
    while (iter++ < MAX_ITER) {
        max_offdiag = 0;

        for (int i = 0; i < (dim_M - 1); i++) {
            for (int j = (i + 1); j < dim_M; j++) {
                float cos;
                float sin;
                float tau;
                float t;

                if (i >= dim_M || j >= dim_M)
                    continue;

                if (fabs(mat[i * dim_M + j]) < EPSILON)
                    continue;

                tau = (mat[j * dim_M + j] - mat[i * dim_M + i]) / (TWO_f * mat[i * dim_M + j]);
                if (tau >= 0.0)
                    t = ONE_f / (tau + sqrtf(ONE_f + tau * tau));
                else
                    t = ONE_f / (tau - sqrtf(ONE_f + tau * tau));

                cos = ONE_f / sqrtf(ONE_f + t * t);
                sin = t * cos;

                /* Update rows i and j of MAT */
                row_i = mat + i * dim_M;
                row_j = mat + j * dim_M;
                avl = dim_M;

                for (; avl > 0; avl -= vl) {
                    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
                    asm volatile ("vle32.v v0, (%0)" :: "r"(row_i));
                    asm volatile ("vle32.v v8, (%0)" :: "r"(row_j));
                    snrt_cluster_hw_barrier();

                    asm volatile ("vfmul.vf v16, v0, %0" :: "f"(cos));
                    asm volatile ("vfmul.vf v24, v8, %0" :: "f"(sin));
                    snrt_cluster_hw_barrier();
                    asm volatile ("vfsub.vv v16, v16, v24");
                    snrt_cluster_hw_barrier();
                    asm volatile ("vse32.v v16, (%0)" :: "r"(row_i));

                    snrt_cluster_hw_barrier();

                    asm volatile ("vfmul.vf v16, v0, %0" :: "f"(sin));
                    asm volatile ("vfmul.vf v24, v8, %0" :: "f"(cos));
                    snrt_cluster_hw_barrier();
                    asm volatile ("vfadd.vv v16, v16, v24");
                    snrt_cluster_hw_barrier();
                    asm volatile ("vse32.v v16, (%0)" :: "r"(row_j));

                    snrt_cluster_hw_barrier();

                    row_i += vl;
                    row_j += vl;
                }

                /* Update cols i and j of MAT */
                col_i = mat + i;
                col_j = mat + j;
                avl = dim_M;

                for (; avl > 0; avl -= vl) {
                    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
                    asm volatile ("vlse32.v v0, (%0), %1" :: "r"(col_i), "r"(stride));
                    asm volatile ("vlse32.v v8, (%0), %1" :: "r"(col_j), "r"(stride));
                    snrt_cluster_hw_barrier();

                    asm volatile ("vfmul.vf v16, v0, %0" :: "f"(cos));
                    asm volatile ("vfmul.vf v24, v8, %0" :: "f"(sin));
                    snrt_cluster_hw_barrier();
                    asm volatile ("vfsub.vv v16, v16, v24");
                    snrt_cluster_hw_barrier();
                    asm volatile ("vsse32.v v16, (%0), %1" :: "r"(col_i), "r"(stride));

                    snrt_cluster_hw_barrier();

                    asm volatile ("vfmul.vf v16, v0, %0" :: "f"(sin));
                    asm volatile ("vfmul.vf v24, v8, %0" :: "f"(cos));
                    snrt_cluster_hw_barrier();
                    asm volatile ("vfadd.vv v16, v16, v24");
                    snrt_cluster_hw_barrier();
                    asm volatile ("vsse32.v v16, (%0), %1" :: "r"(col_j), "r"(stride));

                    snrt_cluster_hw_barrier();

                    col_i += vl * dim_M;
                    col_j += vl * dim_M;
                }

                /* Update cols i and j of V */
                col_i = mat_V + i;
                col_j = mat_V + j;
                avl = dim_M;

                for (; avl > 0; avl -= vl) {
                    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
                    asm volatile ("vlse32.v v0, (%0), %1" :: "r"(col_i), "r"(stride));
                    asm volatile ("vlse32.v v8, (%0), %1" :: "r"(col_j), "r"(stride));
                    snrt_cluster_hw_barrier();

                    asm volatile ("vfmul.vf v16, v0, %0" :: "f"(cos));
                    asm volatile ("vfmul.vf v24, v8, %0" :: "f"(sin));
                    snrt_cluster_hw_barrier();
                    asm volatile ("vfsub.vv v16, v16, v24");
                    snrt_cluster_hw_barrier();
                    asm volatile ("vsse32.v v16, (%0), %1" :: "r"(col_i), "r"(stride));

                    snrt_cluster_hw_barrier();

                    asm volatile ("vfmul.vf v16, v0, %0" :: "f"(sin));
                    asm volatile ("vfmul.vf v24, v8, %0" :: "f"(cos));
                    snrt_cluster_hw_barrier();
                    asm volatile ("vfadd.vv v16, v16, v24");
                    snrt_cluster_hw_barrier();
                    asm volatile ("vsse32.v v16, (%0), %1" :: "r"(col_j), "r"(stride));

                    snrt_cluster_hw_barrier();

                    col_i += vl * dim_M;
                    col_j += vl * dim_M;
                }

                if (fabs(mat[i * dim_M + j]) > max_offdiag)
                    max_offdiag = fabs(mat[i * dim_M + j]);
            }
        }


        if (max_offdiag < EPSILON)
            break;
    }

    /* Extract singular values as sqrtf of diag(MAT) */
    float *p_vec_s;
    float *diag;

    p_vec_s = vec_S;
    diag = mat;

    stride = (dim_M + 1) * sizeof(float);
    avl = dim_M;

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
        asm volatile ("vlse32.v v0, (%0), %1" :: "r"(diag), "r"(stride));
        snrt_cluster_hw_barrier();

        asm volatile ("vfmax.vf v8, v0, %0" :: "f"(0.0f));
        snrt_cluster_hw_barrier();
        asm volatile ("vfsqrt.v v16, v8");
        snrt_cluster_hw_barrier();
        asm volatile ("vse32.v v16, (%0)" :: "r"(p_vec_s));
        snrt_cluster_hw_barrier();

        diag += vl * (dim_M + 1);
        p_vec_s += vl;
    }

    return 0;
}

int linalg_svd_jacobi_impl(float *mat, float *mat_V, float *vec_S, const int dim_M)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = linalg_svd_jacobi_spatz_serial(mat, mat_V, vec_S, dim_M);
#endif

    return ret;
}
