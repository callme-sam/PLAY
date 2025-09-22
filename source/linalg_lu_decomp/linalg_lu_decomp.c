#include "play.h"

#include <math.h>

#include "pmsis.h"

static PI_L1 float ONE_f = 1;

static inline int swap_elems(int *vec, const int idx_a, const int idx_b)
{
    int tmp;

    tmp = vec[idx_a];
    vec[idx_a] = vec[idx_b];
    vec[idx_b] = tmp;

    return 0;
}

static inline int swap_rows(float *mat, const int row_a, const int row_b, const int dim_M, const int dim_N)
{
    for (int n = 0; n < dim_N; n++) {
        int idx_a, idx_b;
        float tmp;

        idx_a = row_a * dim_N + n;
        idx_b = row_b * dim_N + n;

        tmp = mat[idx_a];
        mat[idx_a] = mat[idx_b];
        mat[idx_b] = tmp;
    }

    return 0;
}

// static inline int swap_rows(float *mat, const int row_a, const int row_b, const int dim_M, const int dim_N)
// {
//     int num_ops;
//     int rem_ops;
//     int idx_a;
//     int idx_b;
//     int op;
//     int n;

//     idx_a = row_a * dim_N;
//     idx_b = row_b * dim_N;
//     num_ops = dim_N / 2;
//     rem_ops = dim_N % 2;
//     op = 0;
//     n = 0;

//     do {
//         int idx_a1, idx_a2;
//         int idx_b1, idx_b2;
//         float tmp1, tmp2;

//         idx_a1 = idx_a + n;
//         idx_b1 = idx_b + n;
//         idx_a2 = idx_a + (n + 1);
//         idx_b2 = idx_b + (n + 1);

//         tmp1 = mat[idx_a1];
//         tmp2 = mat[idx_a2];
//         mat[idx_a1] = mat[idx_b1];
//         mat[idx_a2] = mat[idx_b2];
//         mat[idx_b1] = tmp1;
//         mat[idx_b2] = tmp2;

//         n += 2;
//         op++;
//     } while (op < num_ops);

//     if (rem_ops) {
//         int idx_a_end, idx_b_end;
//         float tmp;

//         idx_a_end = idx_a + (dim_N - 1);
//         idx_b_end = idx_b + (dim_N - 1);
//         tmp = mat[idx_a_end];
//         mat[idx_a_end] = mat[idx_b_end];
//         mat[idx_b_end] = tmp;
//     }

//     return 0;
// }

#ifdef  CLUSTER

PI_L1 float pivot;
PI_L1 float p_inv;

static inline int set_permutation_identity(int *vec, const int len)
{
    int num_ops;
    int rem_ops;
    int start;
    int block;
    int left;
    int end;
    int id;
    int op;
    int i;

    id = pi_core_id();
    block = len / NUM_CORES;
    left = len % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);
    num_ops = (start - end) / 2;
    rem_ops = (start - end) % 2;
    i = start;
    op = 0;

    do {
        vec[i] = i;
        vec[i + 1] = (i + 1);

        i += 2;
        op++;
    } while (op < num_ops);

    if (rem_ops)
        vec[end - 1] = (end - 1);

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

}

int linalg_lu_decomp_parallel(const float *mat, float *dst, int *perm, const int dim_M, const int dim_N)
{
    int dim_min;
    int id;

    set_permutation_identity(perm, dim_M);
    matrix_memcpy(mat, dst, dim_M, dim_N);

    id = pi_core_id();
    dim_min = dim_M < dim_N ? dim_M : dim_N;

    for (int k = 0; k < dim_min; k++) {
        if (id == 0) {
            /* Partial Pivoting */
            int row_max;
            float max_val;
            float cur_val;

            row_max = k;
            max_val = fabs(dst[k * dim_N + k]);

            for (int m = k + 1; m < dim_M; m++) {
                cur_val = fabs(dst[m * dim_N + k]);
                if (cur_val > max_val) {
                    row_max = m;
                    max_val = cur_val;
                }
            }

            if (row_max != k) {
                swap_rows(dst, k, row_max, dim_M, dim_N);
                swap_elems(perm, k, row_max);
            }

            pivot = dst[k * dim_N + k];
            if (pivot == 0) {
                printf("ERROR | Zero pivot found at position %d during LU decomposition - Matrix is singular\n", k);
                return -1;
            } else {
                p_inv = ONE_f / pivot;
            }
        }   /* id 0 */

#if NUM_CORES > 1
        pi_cl_team_barrier();
#endif

        /* Gaussian Elimination */
        int start;
        int block;
        int left;
        int end;

        block = (dim_M - (k + 1)) / NUM_CORES;
        left = (dim_M - (k + 1)) % NUM_CORES;
        start = id * block + (id < left ? id : left) + (k + 1);
        end = start + block + (id < left ? 1 : 0);

        for (int m = start; m < end; m++) {
            float factor;

            factor = dst[m * dim_N + k] * p_inv;
            dst[m * dim_N + k] = factor;

            for (int n = k + 1; n < dim_N; n++)
                dst[m * dim_N + n] -= factor * dst[k * dim_N + n];
        }

#if NUM_CORES > 1
        pi_cl_team_barrier();
#endif

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
            swap_rows(dst, k, row_max, dim_M, dim_N);
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

__attribute__((noinline)) int linalg_lu_decomp(const float *mat, float *dst, int *perm, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = linalg_lu_decomp_parallel(mat, dst, perm, dim_M, dim_N);
#else   /* CLUSTER */
    ret = linalg_lu_decomp_serial(mat, dst, perm, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
