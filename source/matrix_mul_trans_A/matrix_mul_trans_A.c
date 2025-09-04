#include "play.h"

#include "pmsis.h"

#ifdef  CLUSTER

int matrix_mul_trans_A_parallel(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    float sum;
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
        for (int p = 0; p < dim_P; p++) {
            sum = 0;
            for (int m = 0; m < dim_M; m++)
                sum += src_a[m * dim_N + n] * src_b[m * dim_P + p];
            dst[n * dim_P + p] = sum;
        }
    }

    return 0;
}

#else   /* CLUSTER */

int matrix_mul_trans_A_serial(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    float sum;

    for (int n = 0; n < dim_N; n++) {
        for (int p = 0; p < dim_P; p++) {
            sum = 0;
            for (int m = 0; m < dim_M; m++)
                sum += src_a[m * dim_N + n] * src_b[m * dim_P + p];
            dst[n * dim_P + p] = sum;
        }
    }

    return 0;
}

#endif  /* CLUSTER */

int matrix_mul_trans_A(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    int ret;

#ifdef  CLUSTER
    ret = matrix_mul_trans_A_parallel(src_a, src_b, dst, dim_M, dim_N, dim_P);
#else   /* CLUSTER */
    ret = matrix_mul_trans_A_serial(src_a, src_b, dst, dim_M, dim_N, dim_P);
#endif  /* CLUSTER */

    return ret;
}
