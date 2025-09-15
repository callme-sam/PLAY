#include "play.h"

#include "pmsis.h"

#ifdef  CLUSTER

static inline void mat_vec_mul(const float *mat, const float *vec_x, const int n, const int dim_M, const int dim_N, float *sum1, float *sum2)
{
    int num_ops;
    int ops;
    int m;

    m = 0;
    ops = 0;
    *sum1 = 0;
    *sum2 = 0;
    num_ops = dim_M / 2;
    do {
        float mat1, mat2;
        float vec1, vec2;

        mat1 = mat[m * dim_N + n];
        mat2 = mat[(m + 1) * dim_N + n];
        vec1 = vec_x[m];
        vec2 = vec_x[m + 1];

        *sum1 += mat1 * vec1;
        *sum2 += mat2 * vec2;

        m += 2;
        ops++;
    } while (ops < num_ops);
}

int linalg_gemv_trans_parallel(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N)
{
    int row_start;
    int row_end;
    int rem_ops;
    float sum1;
    float sum2;
    int block;
    int left;
    int id;
    int n;

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
    rem_ops = dim_M % 2;

    n = row_start;
    if (rem_ops) {
        /* loop unroll will have leftovers */
        do {
            mat_vec_mul(mat, vec_x, n, dim_M, dim_N, &sum1, &sum2);
            /* leftover */
            sum1 += mat[(dim_M - 1) * dim_N + n] * vec_x[dim_M - 1];
            dst[n] = alpha * (sum1 + sum2) + beta * vec_y[n];
            n++;
        } while (n < row_end);

    } else {
        /* loop unroll will NOT have leftovers */
        do {
            mat_vec_mul(mat, vec_x, n, dim_M, dim_N, &sum1, &sum2);
            dst[n] = alpha * (sum1 + sum2) + beta * vec_y[n];
            n++;
        } while (n < row_end);
    }

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

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


__attribute__((noinline)) int linalg_gemv_trans(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = linalg_gemv_trans_parallel(mat, vec_x, vec_y, alpha, beta, dst, dim_M, dim_N);
#else   /* CLUSTER */
    ret = linalg_gemv_trans_serial(mat, vec_x, vec_y, alpha, beta, dst, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
