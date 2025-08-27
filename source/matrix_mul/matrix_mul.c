#include "play.h"

#include "pmsis.h"

#ifdef  CLUSTER

int matrix_mul_parallel(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    int row_start;
    int row_end;
    float sum;
    int block;
    int left;
    int id;

    id = pi_core_id();
    block = dim_M / NUM_CORES;
    left = dim_M % NUM_CORES;
    row_start = id * block + (id < left ? id : left);
    row_end = row_start + block + (id < left ? 1 : 0);

    for (int m = row_start; m < row_end; m++) {
        for (int p = 0; p < dim_P; p++) {
            sum = 0;
            for (int n = 0; n < dim_N; n++)
                sum += src_a[m * dim_N + n] * src_b[n * dim_P + p];
            dst[m * dim_P + p] = sum;
        }
    }

    return 0;
}

#else   /* CLUSTER */

int matrix_mul_serial(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    float sum;

    for (int m = 0; m < dim_M; m++) {
        for (int p = 0; p < dim_P; p++) {
            sum = 0;
            for (int n = 0; n < dim_N; n++)
                sum += src_a[m * dim_N + n] * src_b[n * dim_P + p];
            dst[m * dim_P + p] = sum;
        }
    }

    return 0;
}

#endif  /* CLUSTER */

int matrix_mul(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    int ret;

#ifdef  CLUSTER
    ret = matrix_mul_parallel(src_a, src_b, dst, dim_M, dim_N, dim_P);
#else   /* CLUSTER */
    ret = matrix_mul_serial(src_a, src_b, dst, dim_M, dim_N, dim_P);
#endif  /* CLUSTER */

    return ret;
}
