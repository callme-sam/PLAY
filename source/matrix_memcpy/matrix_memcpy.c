#include "play.h"

#include "pmsis.h"


#ifdef  CLUSTER

int matrix_memcpy_parallel(const float *src, float *dst, const int dim_M, const int dim_N)
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
            dst[m * dim_N + n] = src[m * dim_N + n];

    return 0;
}

#else   /* CLUSTER */

int matrix_memcpy_serial(const float *src, float *dst, const int dim_M, const int dim_N)
{
    for (int m = 0; m < dim_M; m++)
        for (int n = 0; n < dim_N; n++)
            dst[m * dim_N + n] = src[m * dim_N + n];

    return 0;
}

#endif  /* CLUSTER */

int matrix_memcpy(const float *src, float *dst, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = matrix_memcpy_parallel(src, dst, dim_M, dim_N);
#else   /* CLUSTER */
    ret = matrix_memcpy_serial(src, dst, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
