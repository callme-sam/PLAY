#include "internal/arch_interface.h"
#include "play.h"

#include <math.h>

#include "snrt.h"

#ifdef ENABLE_LOGGING
#include "printf.h"
#endif

__attribute__((always_inline)) static int swap_elems(int *vec, const int idx_a, const int idx_b)
{
    int tmp;

    tmp = vec[idx_a];
    vec[idx_a] = vec[idx_b];
    vec[idx_b] = tmp;

    return 0;
}

__attribute__((always_inline)) static int rvv_set_perm_identity(int *vec, const int len)
{
#if 0   /* vid.v not supported */
    int *p_vec;
    size_t avl;
    size_t vl;
    int idx;

    p_vec = vec;
    avl = len;
    idx = 0;

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vid.v v0");


    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vadd.vx v8, v0, %0" :: "r"(idx));

        asm volatile ("vse32.v v8, (%0)" :: "r"(p_vec));

        p_vec += vl;
        idx += vl;
    }
#else
    for (int i = 0; i < len; i++)
        vec[i] = i;
#endif

    return 0;
}

__attribute__((always_inline)) static int rvv_gaussian_elimination(float *mat, float factor, const int dim_N, int m, int k)
{
    float *row_m;
    float *row_k;
    size_t avl;
    size_t vl;

    avl = dim_N - (k + 1);
    row_m = mat + (m * dim_N + (k + 1));
    row_k = mat + (k * dim_N + (k + 1));

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vle32.v v0, (%0)" :: "r"(row_m));
        asm volatile ("vle32.v v8, (%0)" :: "r"(row_k));
        snrt_cluster_hw_barrier();

        asm volatile ("vfnmsac.vf v0, %0, v8" :: "f"(factor));

        asm volatile ("vse32.v v0, (%0)" :: "r"(row_m));

        row_m += vl;
        row_k += vl;
    }

    return 0;
}

// #define SCALAR
#define HALF_RVV
// #define FULL_RVV    /* DONT! vfist.m not supported */

#ifdef SCALAR

__attribute__((always_inline)) static int rvv_find_max_val(float *mat, const int dim_M, const int dim_N, int *max_idx, int col)
{
    float max;
    float val;

    *max_idx = col;
    max = fabs(mat[col * dim_N + col]);
    for (int m = col + 1; m < dim_M; m++) {
        val = fabs(mat[m * dim_N + col]);
        if (val > max) {
            *max_idx = m;
            max = val;
        }
    }

    return 0;
}

#elif defined(HALF_RVV)

#include <math.h>

__attribute__((always_inline)) static int rvv_find_max_val(float *mat, const int dim_M, const int dim_N, int *max_idx, int col)
{
    float ZERO_f = 0.0f;

    size_t stride;
    float *row_m;
    size_t avl;
    size_t vl;
    float max;

    row_m = mat + col * dim_N + col;
    stride = dim_N * sizeof(float);
    avl = dim_M - col;

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vfmv.v.f v0, %0" :: "f"(ZERO_f));

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vlse32.v v8, (%0), %1" :: "r"(row_m), "r"(stride));
        snrt_cluster_hw_barrier();

        asm volatile ("vfabs.v v8, v8");
        asm volatile ("vfmax.vv v0, v8, v0");

        row_m += vl * dim_N;
    }

    asm volatile ("vfredmax.vs v0, v0, v0");
    // snrt_cluster_hw_barrier();   // TODO: find out why performances get worse if these barriers are removed
    asm volatile ("vfmv.f.s %0, v0" : "=f"(max));
    // snrt_cluster_hw_barrier();

    *max_idx = col;
    for (int m = col; m < dim_M; m++) {
        float val = fabs(mat[m * dim_N + col]);
        if (val == max)
            *max_idx = m;
    }

    return 0;
}

#elif defined(FULL_RVV)

#include <math.h>

__attribute__((always_inline)) static int rvv_find_max_val(float *mat, const int dim_M, const int dim_N, int *max_idx, int col)
{
    float ZERO_f = 0.0f;

    size_t stride;
    float *row_m;
    size_t avl;
    size_t vl;
    float max;

    row_m = mat + col * dim_N + col;
    stride = dim_N * sizeof(float);
    avl = dim_M - col;

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vfmv.v.f v0, %0" :: "f"(ZERO_f));

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vlse32.v v8, (%0), %1" :: "r"(row_m), "r"(stride));
        snrt_cluster_hw_barrier();

        asm volatile ("vfabs.v v8, v8");
        asm volatile ("vfmax.vv v0, v8, v0");

        row_m += vl * dim_N;
    }

    asm volatile ("vfredmax.vs v0, v0, v0");
    snrt_cluster_hw_barrier();
    asm volatile ("vfmv.f.s %0, v0" : "=f"(max));
    snrt_cluster_hw_barrier();

    int base_idx;
    int local_idx;

    row_m = mat + col * dim_N + col;
    avl = dim_M - col;
    base_idx = col;
    *max_idx = col;

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vlse32.v v0, (%0), %1" :: "r"(row_m), "r"(stride));
        snrt_cluster_hw_barrier();

        asm volatile ("vfabs.v v0, v0");
        asm volatile ("vmfeq.vf v8, v0, %0" :: "f"(max));
        snrt_cluster_hw_barrier();

        asm volatile ("vfirst.m %0, v8" : "=r"(local_idx));
        snrt_cluster_hw_barrier();

        if (local_idx >= 0) {
            *max_idx = local_idx;
            break;
        }

        row_m += vl * dim_N;
        base_idx += vl;
    }

    return 0;
}

#endif

static int linalg_lu_decomp_spatz_serial(float *mat, int *perm, const int dim_M, const int dim_N)
{
    float factor;
    float pivot;
    int dim_min;
    int row_max;

    rvv_set_perm_identity(perm, dim_M);

    dim_min = dim_M < dim_N ? dim_M : dim_N;
    for (int k = 0; k < dim_min; k++) {

        /* Partial Pivoting */
        rvv_find_max_val(mat, dim_M, dim_N, &row_max, k);

        if (row_max != k) {
            matrix_swap_rows(mat, k, row_max, dim_N);
            swap_elems(perm, k, row_max);
        }

        /* Gaussian Elimination */
        pivot = mat[k * dim_N + k];
        if (pivot == 0) {
#ifdef  ENABLE_LOGGING
            printf("ERROR | Zero pivot found at position %d during LU decomposition - Matrix is singular\n", k);
#endif  /* ENABLE_LOGGING */
            snrt_exit(-1);
        }

        for (int m = k + 1; m < dim_M; m++) {
            factor = mat[m * dim_N + k] / pivot;
            mat[m * dim_N + k] = factor;

            rvv_gaussian_elimination(mat, factor, dim_N, m, k);
        }
    }

    return 0;
}

int linalg_lu_decomp_impl(float *mat, int *perm, const int dim_M, const int dim_N)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = linalg_lu_decomp_spatz_serial(mat, perm, dim_M, dim_N);
#endif

    return ret;
}
