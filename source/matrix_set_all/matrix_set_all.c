#include "play.h"

#include "pmsis.h"


#ifdef  CLUSTER

int matrix_set_all_parallel(float *mat, const float val, const int dim_M, const int dim_N)
{
    int row_start;
    int row_end;
    int num_ops;
    int rem_ops;
    int block;
    int left;
    int m, n;
    int ops;
    int id;

    id = pi_core_id();
    block = dim_M / NUM_CORES;
    left = dim_M % NUM_CORES;
    row_start = id * block + (id < left ? id : left);
    row_end = row_start + block + (id < left ? 1 : 0);
    num_ops = dim_N / 2;
    rem_ops = dim_N % 2;

    m = row_start;
    do {
        n = 0;
        ops = 0;
        do {
            mat[m * dim_N + n] = val;
            mat[m * dim_N + (n + 1)] = val;

            n += 2;
            ops++;
        } while (ops < num_ops);
        m++;
    } while (m < row_end);

    if (rem_ops) {
        m = row_start;
        do {
            mat[m * dim_N + (dim_N - 1)] = val;
            m++;
        } while (m < row_end);
    }

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}

#else   /* CLUSTER */

int matrix_set_all_serial(float *mat, const float val, const int dim_M, const int dim_N)
{
    for (int m = 0; m < dim_M; m++)
        for (int n = 0; n < dim_N; n++)
            mat[m * dim_N + n] = val;

    return 0;
}

#endif  /* CLUSTER */


__attribute__((noinline)) int matrix_set_all(float *mat, const float val, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = matrix_set_all_parallel(mat, val, dim_M, dim_N);
#else   /* CLUSTER */
    ret = matrix_set_all_serial(mat, val, dim_M, dim_N);
#endif  /* CLUSTER */

}
