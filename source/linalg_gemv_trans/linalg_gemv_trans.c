#include "play.h"

#include "pmsis.h"

#ifdef  CLUSTER

int linalg_gemv_trans_parallel(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N)
{
    int row_start;
    int row_end;
    float sum;
    int block;
    int left;
    int id;

    if (alpha == 0.0f) {
        if (beta == 0.0f)
            vector_set_all(dst, 0.0, dim_M);
        else if (beta == 1.0f)
            vector_memcpy(vec_y, dst, dim_M);
        else
            vector_scale(vec_y, beta, dst, dim_M);
        return 0;
    }

    id = pi_core_id();
    block = dim_N / NUM_CORES;
    left = dim_N % NUM_CORES;
    row_start = id * block + (id < left ? id : left);
    row_end = row_start + block + (id < left ? 1 : 0);

    for (int n = row_start; n < dim_N; n++) {
        sum = 0;
        for (int m = 0; m < dim_M; m++)
            sum += mat[m * dim_N + n] * vec_x[m];
        dst[n] = alpha * sum + beta * vec_y[n];
    }

    return 0;
}

#else   /* CLUSTER */

int linalg_gemv_trans_serial(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N)
{
    float sum;

    if (alpha == 0.0f) {
        if (beta == 0.0f)
            vector_set_all(dst, 0.0, dim_M);
        else if (beta == 1.0f)
            vector_memcpy(vec_y, dst, dim_M);
        else
            vector_scale(vec_y, beta, dst, dim_M);
        return 0;
    }

    for (int n = 0; n < dim_N; n++) {
        sum = 0;
        for (int m = 0; m < dim_M; m++)
            sum += mat[m * dim_N + n] * vec_x[m];
        dst[n] = alpha * sum + beta * vec_y[n];
    }

    return 0;
}
#endif  /* CLUSTER */


int linalg_gemv_trans(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = linalg_gemv_trans_parallel(mat, vec_x, vec_y, alpha, beta, dst, dim_M, dim_N);
#else   /* CLUSTER */
    ret = linalg_gemv_trans_serial(mat, vec_x, vec_y, alpha, beta, dst, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
