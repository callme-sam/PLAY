#include "play.h"

#include "pmsis.h"

#ifdef CLUSTER

#if 1
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
#endif

#if 0
int matrix_swap_rows_parallel(float *mat, const int row_a, const int row_b, const int dim_M, const int dim_N)
{
    int tot_ops;
    int rem_ops;
    float tmp1;
    float tmp2;
    int block;
    int start;
    int left;
    int end;
    int id;
    int op;
    int n;

    id = pi_core_id();
    block = dim_N / NUM_CORES;
    left = dim_N % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);
    tot_ops = (end - start) / 2;
    rem_ops = tot_ops % 2;
    n = start;
    op = 0;

    do {
        int idx_a1, idx_a2;
        int idx_b1, idx_b2;
        float src_a1, src_a2;
        float src_b1, src_b2;

        idx_a1 = row_a * dim_N + n;
        idx_b1 = row_b * dim_N + n;
        idx_a2 = row_a * dim_N + (n + 1);
        idx_b2 = row_b * dim_N + (n + 1);

        src_a1 = mat[idx_a1];
        src_b1 = mat[idx_b1];
        src_a2 = mat[idx_a2];
        src_b2 = mat[idx_b2];

        mat[idx_a1] = src_b1;
        mat[idx_a2] = src_b2;
        mat[idx_b1] = src_a1;
        mat[idx_b2] = src_a2;

        n += 2;
        op++;
    } while (op < tot_ops);

    if (rem_ops) {
        int idx_a, idx_b;
        float tmp;

        idx_a = row_a * dim_N + (dim_N - 1);
        idx_b = row_b * dim_N + (dim_N - 1);

        tmp = mat[idx_a];
        mat[idx_a] = mat[idx_b];
        mat[idx_b] = tmp;
    }

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}
#endif

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
