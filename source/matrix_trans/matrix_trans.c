#include "play.h"

#include "pmsis.h"

#ifdef  CLUSTER

int matrix_trans_parallel(const float *src, float *dst, const int dim_M, const int dim_N)
{
    int row_start;
    int row_end;
    int block;
    int left;
    int id;

    id = pi_core_id();
    block = dim_M / NUM_CORES;
    left = dim_M % NUM_CORES;
    row_start = id * block + (id < left ? id : left);
    row_end = row_start + block + (id < left ? 1 : 0);

    for (int m = row_start; m < row_end; m++)
        for (int n = 0; n < dim_N; n++)
            dst[n * dim_M + m] = src[m * dim_N + n];

    return 0;
}

#else   /* CLUSTER */

int matrix_trans_serial(const float *src, float *dst, const int dim_M, const int dim_N)
{
    for (int m = 0; m < dim_M; m++)
        for (int n = 0; n < dim_N; n++)
            dst[n * dim_M + m] = src[m * dim_N + n];

    return 0;
}

#endif  /* CLUSTER */

int matrix_trans(const float *src, float *dst, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = matrix_trans_parallel(src, dst, dim_M, dim_N);
#else   /* CLUSTER */
    ret = matrix_trans_serial(src, dst, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
