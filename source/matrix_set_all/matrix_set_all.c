#include "play.h"

#include "pmsis.h"


#ifdef  CLUSTER

int matrix_set_all_parallel(float *mat, const float val, const int dim_M, const int dim_N)
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
            mat[m * dim_N + n] = val;

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


int matrix_set_all(float *mat, const float val, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = matrix_set_all_parallel(mat, val, dim_M, dim_N);
#else   /* CLUSTER */
    ret = matrix_set_all_serial(mat, val, dim_M, dim_N);
#endif  /* CLUSTER */

}
