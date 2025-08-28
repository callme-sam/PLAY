#include "play.h"

#include "pmsis.h"

#ifdef  CLUSTER

static int matrix_mul_trans_parallel(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
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
                sum += src_a[m * dim_N + n] * src_b[p * dim_N + n];
            dst[m * dim_P + p] = sum;
        }
    }

    return 0;
}

#else   /* CLUSTER */

static int matrix_mul_trans_serial(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    float sum;

    for (int m = 0; m < dim_M; m++) {
        for (int p = 0; p < dim_P; p++) {
            sum = 0;
            for (int n = 0; n < dim_N; n++)
                sum += src_a[m * dim_N + n] * src_b[p * dim_N + n];
            dst[m * dim_P + p] = sum;
        }
    }

    return 0;
}

#endif  /* CLUSTER */

int matrix_mul_trans(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    int ret;

#ifdef  CLUSTER
    ret = matrix_mul_trans_parallel(src_a, src_b, dst, dim_M, dim_N, dim_P);
#else   /* CLUSTER */
    ret = matrix_mul_trans_serial(src_a, src_b, dst, dim_M, dim_N, dim_P);
#endif  /* CLUSTER */

    return ret;
}
