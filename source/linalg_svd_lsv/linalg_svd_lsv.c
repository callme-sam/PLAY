#include "play.h"

#include "pmsis.h"

#define EPSILON     (1e-12)

#ifdef  CLUSTER

int linalg_svd_lsv_parallel(const float *src, float *mat_V, float *vec_S, float *dst, const int dim_M, const int dim_N)
{
    int block;
    float sum;
    int start;
    int left;
    int end;
    int id;

    id = pi_core_id();
    block = dim_N / NUM_CORES;
    left = dim_N % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);

    for (int k = start; k < end; k++) {
        /* Optimization */
        if (vec_S[k] < EPSILON) {
            /* Set k-th column of dst to 0 */
            for (int m = 0; m < dim_M; m++)
                dst[m * dim_N + k] = 0;
            continue;
        }

        for (int m = 0; m < dim_M; m++) {
            sum = 0;
            for (int n = 0; n < dim_N; n++)
                sum += src[m * dim_N + n] * mat_V[n * dim_N + k];
            dst[m * dim_N + k] = sum / vec_S[k];
        }
    }

    return 0;
}

#else   /* CLUSTER */

int linalg_svd_lsv_serial(const float *src, float *mat_V, float *vec_S, float *dst, const int dim_M, const int dim_N)
{
    float sum;

    for (int k = 0; k < dim_N; k++) {
        /* Optimization */
        if (vec_S[k] < EPSILON) {
            /* Set k-th column of dst to 0 */
            for (int m = 0; m < dim_M; m++)
                dst[m * dim_N + k] = 0;
            continue;
        }

        for (int m = 0; m < dim_M; m++) {
            sum = 0;
            for (int n = 0; n < dim_N; n++)
                sum += src[m * dim_N + n] * mat_V[n * dim_N + k];
            dst[m * dim_N + k] = sum / vec_S[k];
        }
    }
}

#endif  /* CLUSTER */

int linalg_svd_lsv(const float *src, float *mat_V, float *vec_S, float *dst, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = linalg_svd_lsv_parallel(src, mat_V, vec_S, dst, dim_M, dim_N);
#else   /* CLUSTER */
    ret = linalg_svd_lsv_serial(src, mat_V, vec_S, dst, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
