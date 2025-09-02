#include "play.h"

#include "pmsis.h"

PI_L1 float *y;

#ifdef  CLUSTER
PI_L1 float local_sum[NUM_CORES];

int linalg_lu_solve_parallel(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    int perm_idx;
    float sum;

    int start;
    int block;
    int left;
    int end;
    int id;

    id = pi_core_id();
    if (id == 0)
        y = pmsis_l1_malloc(dim_M * sizeof(float));

    /* Forward substitution (L * y = perm * v) */
    for (int m = 0; m < dim_M; m++) {
        sum = 0;
        local_sum[id] = 0;
        perm_idx = perm[m];

        block = m / NUM_CORES;
        left = m % NUM_CORES;
        start = id * block + (id < left ? id : left);
        end = start + block + (id < left ? 1 : 0);

        for (int k = start; k < end; k++)
            local_sum[id] += mat[m * dim_N + k] * y[k];

        pi_cl_team_barrier();
        if (id == 0) {
            for (int i = 0; i < NUM_CORES; i++)
                sum += local_sum[i];
            y[m] = vec[perm_idx] - sum;
        }
        pi_cl_team_barrier();
    }

    /* Backward substitution (U * x = y) */
    for (int m = (dim_M - 1); m >= 0; m--) {
        sum = 0;
        local_sum[id] = 0;

        block = (dim_N - (m + 1)) / NUM_CORES;
        left = (dim_N - (m + 1)) % NUM_CORES;
        start = id * block + (id < left ? id : left) + (m + 1);
        end = start + block + (id < left ? 1 : 0);

        for (int k = start; k < end; k++)
            local_sum[id] += mat[m * dim_N + k] * result[k];

        pi_cl_team_barrier();
        if (id == 0) {
            for (int i = 0; i < NUM_CORES; i++)
                sum += local_sum[i];
            result[m] = (y[m] - sum) / mat[m * dim_N + m];
        }
        pi_cl_team_barrier();
    }

    if (id == 0)
        pmsis_l1_malloc_free(y, dim_M * sizeof(float));

    return 0;
}

#else   /* CLUSTER */

int linalg_lu_solve_serial(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    int perm_idx;
    float sum;

    y = pmsis_l1_malloc(dim_M * sizeof(float));

    /* Forward substitution (L * y = perm * v) */
    for (int m = 0; m < dim_M; m++) {
        sum = 0;
        perm_idx = perm[m];

        for (int k = 0; k < m; k++)
            sum += mat[m * dim_N + k] * y[k];
        y[m] = vec[perm_idx] - sum;
    }

    /* Backward substitution (U * x = y) */
    for (int m = (dim_M - 1); m >= 0; m--) {
        sum = 0;

        for (int k = (m + 1); k < dim_N; k++)
            sum += mat[m * dim_N + k] * result[k];
        result[m] = (y[m] - sum) / mat[m * dim_N + m];
    }

    return 0;
}

#endif  /* CLUSTER */

int linalg_lu_solve(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = linalg_lu_solve_parallel(mat, vec, perm, result, dim_M, dim_N);
#else   /* CLUSTER */
    ret = linalg_lu_solve_serial(mat, vec, perm, result, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
