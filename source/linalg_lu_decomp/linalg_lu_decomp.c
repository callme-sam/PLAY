#include "play.h"

#include <math.h>

#include "pmsis.h"

static int swap_elems(int *vec, const int idx_a, const int idx_b)
{
    int tmp;

    tmp = vec[idx_a];
    vec[idx_a] = vec[idx_b];
    vec[idx_b] = tmp;

    return 0;
}

#ifdef  CLUSTER

static int set_permutation_identity(int *vec, const int len)
{
    int start;
    int block;
    int left;
    int end;
    int id;

    id = pi_core_id();
    block = len / NUM_CORES;
    left = len % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);

    for (int i = start; i < end; i++)
        vec[i] = i;

}

int linalg_lu_decomp_parallel(const float *mat, float *dst, int *perm, const int dim_M, const int dim_N)
{
    float factor;
    float pivot;
    int dim_min;
    int row_max;
    float max;
    float val;

    int start;
    int block;
    int left;
    int end;
    int id;

    set_permutation_identity(perm, dim_M);
    matrix_memcpy(mat, dst, dim_M, dim_N);
    id = pi_core_id();

    dim_min = dim_M < dim_N ? dim_M : dim_N;
    for (int k = 0; k < dim_min; k++) {

        if (id == 0) {
            /* Partial Pivoting */
            row_max = k;
            max = fabs(dst[k * dim_N + k]);
            for (int m = k + 1; m < dim_M; m++) {
                val = fabs(dst[m * dim_N + k]);
                if (val > max) {
                    row_max = m;
                    max = val;
                }
            }

            if (row_max != k) {
                matrix_swap_rows(dst, k, row_max, dim_M, dim_N);
                swap_elems(perm, k, row_max);
            }

            /* Gaussian Elimination */
            pivot = dst[k * dim_N + k];
            if (pivot == 0) {
                printf("ERROR | Zero pivot found at position %d during LU decomposition - Matrix is singular\n", k);
                return -1;
            }
        }

        block = (dim_M - (k + 1)) / NUM_CORES;
        left = (dim_M - (k + 1)) % NUM_CORES;
        start = id * block + (id < left ? id : left) + (k + 1);
        end = start + block + (id < left ? 1 : 0) + (k + 1);

        pi_cl_team_barrier();
        for (int m = start; m < end; m++) {
            factor = dst[m * dim_N + k] / pivot;
            dst[m * dim_N + k] = factor;

            for (int n = k + 1; n < dim_N; n++)
                dst[m * dim_N + n] -= factor * dst[k * dim_N + n];
        }
        pi_cl_team_barrier();
    }

    return 0;
}

#else   /* CLUSTER */

static int set_permutation_identity(int *vec, const int len)
{
    for (int i = 0; i < len; i++)
        vec[i] = i;
}

int linalg_lu_decomp_serial(const float *mat, float *dst, int *perm, const int dim_M, const int dim_N)
{
    float factor;
    float pivot;
    int dim_min;
    int row_max;
    float max;
    float val;

    set_permutation_identity(perm, dim_M);
    matrix_memcpy(mat, dst, dim_M, dim_N);

    dim_min = dim_M < dim_N ? dim_M : dim_N;
    for (int k = 0; k < dim_min; k++) {

        /* Partial Pivoting */
        row_max = k;
        max = fabs(dst[k * dim_N + k]);
        for (int m = k + 1; m < dim_M; m++) {
            val = fabs(dst[m * dim_N + k]);
            if (val > max) {
                row_max = m;
                max = val;
            }
        }

        if (row_max != k) {
            matrix_swap_rows(dst, k, row_max, dim_M, dim_N);
            swap_elems(perm, k, row_max);
        }

        /* Gaussian Elimination */
        pivot = dst[k * dim_N + k];
        if (pivot == 0) {
            printf("ERROR | Zero pivot found at position %d during LU decomposition - Matrix is singular\n", k);
            return -1;
        }

        for (int m = k + 1; m < dim_M; m++) {
            factor = dst[m * dim_N + k] / pivot;
            dst[m * dim_N + k] = factor;

            for (int n = k + 1; n < dim_N; n++)
                dst[m * dim_N + n] -= factor * dst[k * dim_N + n];
        }
    }

    return 0;
}

#endif  /* CLUSTER */

int linalg_lu_decomp(const float *mat, float *dst, int *perm, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = linalg_lu_decomp_parallel(mat, dst, perm, dim_M, dim_N);
#else   /* CLUSTER */
    ret = linalg_lu_decomp_serial(mat, dst, perm, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
