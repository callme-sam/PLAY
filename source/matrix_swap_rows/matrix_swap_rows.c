#include "play.h"

#include "pmsis.h"

#ifdef CLUSTER

int matrix_swap_rows_parallel(float *mat, const int row_a, const int row_b, const int dim_M, const int dim_N)
{
    float tmp;
    int start;
    int block;
    int left;
    int end;
    int id;

    id = pi_core_id();
    block = dim_N / NUM_CORES;
    left = dim_N % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);

    for (int n = start; n < end; n++) {
        tmp = mat[row_a * dim_N + n];
        mat[row_a * dim_N + n] = mat[row_b * dim_N + n];
        mat[row_b * dim_N + n] = tmp;
    }

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}

#else   /* CLUSTER */

int matrix_swap_rows_serial(float *mat, const int row_a, const int row_b, const int dim_M, const int dim_N)
{
    float tmp;

    for (int n = 0; n < dim_N; n++) {
        tmp = mat[row_a * dim_N + n];
        mat[row_a * dim_N + n] = mat[row_b * dim_N + n];
        mat[row_b * dim_N + n] = tmp;
    }

    return 0;
}

#endif  /* CLUSTER */

__attribute__((noinline)) int matrix_swap_rows(float *mat, const int row_a, const int row_b, const int dim_M, const int dim_N)
{
    int ret;

#ifdef CLUSTER
    ret = matrix_swap_rows_parallel(mat, row_a, row_b, dim_M, dim_N);
#else   /* CLUSTER */
    ret = matrix_swap_rows_serial(mat, row_a, row_b, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
