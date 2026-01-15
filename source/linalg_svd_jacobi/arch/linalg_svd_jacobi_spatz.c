#include "internal/arch_interface.h"
#include "play.h"

#include <math.h>

#include "snrt.h"

__attribute__((always_inline)) static int rvv_matrix_set_identity(float *mat, const int dim_M)
{
    const float ONE_f = 1.0f;
    float *p_diag;

    size_t stride;
    size_t avl;
    size_t vl;

    stride = (dim_M + 1) * sizeof(float);   // +1 to store elements only on the diag
    p_diag = mat;
    avl = dim_M;

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vfmv.v.f v0, %0" :: "f"(ONE_f));

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
        asm volatile ("vsse32.v v0, (%0), %1" :: "r"(p_diag), "r"(stride));

        p_diag += vl;
    }

    return 0;
}

__attribute__((always_inline)) static int rvv_row_jacobi_rotation(float *mat, const int i, const int j, const float cos, const float sin, const int dim)
{
    size_t stride;
    size_t avl;
    size_t vl;

    float *row_i;
    float *row_j;

    stride = dim * sizeof(float);
    row_i = mat + (i * dim);
    row_j = mat + (j * dim);
    avl = dim;

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
        asm volatile ("vle32.v v0, (%0)" :: "r"(row_i));
        asm volatile ("vle32.v v8, (%0)" :: "r"(row_j));

        asm volatile ("vfmul.vf v16, v0, %0" :: "f"(cos));
        asm volatile ("vfmul.vf v24, v8, %0" :: "f"(sin));
        asm volatile ("vfsub.vv v16, v16, v24");
        asm volatile ("vse32.v v16, (%0)" :: "r"(row_i));


        asm volatile ("vfmul.vf v16, v0, %0" :: "f"(sin));
        asm volatile ("vfmul.vf v24, v8, %0" :: "f"(cos));
        asm volatile ("vfadd.vv v16, v16, v24");
        asm volatile ("vse32.v v16, (%0)" :: "r"(row_j));

        row_i += vl;
        row_j += vl;
    }

    return 0;
}

__attribute__((always_inline)) static int rvv_col_jacobi_rotation(float *mat, const int i, const int j, const float cos, const float sin, const int dim)
{
    size_t stride;
    size_t avl;
    size_t vl;

    float *col_i;
    float *col_j;

    stride = dim * sizeof(float);
    col_i = mat + i;
    col_j = mat + j;
    avl = dim;

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vlse32.v v0, (%0), %1" :: "r"(col_i), "r"(stride));
        asm volatile ("vlse32.v v8, (%0), %1" :: "r"(col_j), "r"(stride));
        snrt_cluster_hw_barrier();

        asm volatile ("vfmul.vf v16, v0, %0" :: "f"(cos));
        asm volatile ("vfmul.vf v24, v8, %0" :: "f"(sin));
        asm volatile ("vfsub.vv v16, v16, v24");
        asm volatile ("vsse32.v v16, (%0), %1" :: "r"(col_i), "r"(stride));

        asm volatile ("vfmul.vf v16, v0, %0" :: "f"(sin));
        asm volatile ("vfmul.vf v24, v8, %0" :: "f"(cos));
        asm volatile ("vfadd.vv v16, v16, v24");
        asm volatile ("vsse32.v v16, (%0), %1" :: "r"(col_j), "r"(stride));

        col_i += vl * dim;
        col_j += vl * dim;
    }

    return 0;
}

__attribute__((always_inline)) static int rvv_get_singular_values(float *mat, float *vec_S, const int dim)
{
    float ZERO_f = 0.0f;

    size_t stride;
    size_t avl;
    size_t vl;

    float *p_diag;
    float *p_vec;

    stride = (dim + 1) * sizeof(float); // +1 to load elements only on the diag
    p_vec = vec_S;
    p_diag = mat;
    avl = dim;

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
        asm volatile ("vlse32.v v0, (%0), %1" :: "r"(p_diag), "r"(stride));
        snrt_cluster_hw_barrier();

        asm volatile ("vfmax.vf v8, v0, %0" :: "f"(ZERO_f));
        asm volatile ("vfsqrt.v v16, v8");
        asm volatile ("vse32.v v16, (%0)" :: "r"(p_vec));

        p_diag += vl * (dim + 1);
        p_vec += vl;
    }

    return 0;
}

static int linalg_svd_jacobi_spatz_serial(float *mat, float *mat_V, float *vec_S, const int dim_M)
{
    float ZERO_f = 0.0f;
    float ONE_f = 1.0f;
    float TWO_f = 2.0f;
    int MAX_ITER = 800;
    float EPSILON = 1e-12;

    float max_offdiag;
    int iter;

    size_t avl;
    size_t vl;

    rvv_matrix_set_identity(mat_V, dim_M);

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
                if (tau >= ZERO_f)
                    t = ONE_f / (tau + sqrtf(ONE_f + tau * tau));
                else
                    t = ONE_f / (tau - sqrtf(ONE_f + tau * tau));

                cos = ONE_f / sqrtf(ONE_f + t * t);
                sin = t * cos;
                snrt_cluster_hw_barrier();

                /* Update rows i and j of MAT */
                rvv_row_jacobi_rotation(mat, i, j, cos, sin, dim_M);

                /* Update cols i and j of MAT */
                rvv_col_jacobi_rotation(mat, i, j, cos, sin, dim_M);

                /* Update cols i and j of V */
                rvv_col_jacobi_rotation(mat_V, i, j, cos, sin, dim_M);

                if (fabs(mat[i * dim_M + j]) > max_offdiag)
                    max_offdiag = fabs(mat[i * dim_M + j]);
            }
        }

        if (max_offdiag < EPSILON)
            break;
    }

    /* Extract singular values as sqrtf of diag(MAT) */
    rvv_get_singular_values(mat, vec_S, dim_M);

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
