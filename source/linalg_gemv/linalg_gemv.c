#include "play.h"

#include "pmsis.h"

#ifdef  CLUSTER

static inline void mat_vec_mul(const float *mat, const float *vec_x, const int m, const int dim_M, const int dim_N, float *sum1, float *sum2)
{
    int num_ops;
    int ops;
    int n;

    n = 0;
    ops = 0;
    *sum1 = 0;
    *sum2 = 0;
    num_ops = dim_N / 2;
    do {
        float mat1, mat2;
        float vec1, vec2;

        mat1 = mat[m * dim_N + n];
        mat2 = mat[m * dim_N + (n + 1)];
        vec1 = vec_x[n];
        vec2 = vec_x[n + 1];

        *sum1 += mat1 * vec1;
        *sum2 += mat2 * vec2;

        n += 2;
        ops++;
    } while (ops < num_ops);
}

int linalg_gemv_parallel(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N)
{
    int row_start;
    int row_end;
    int rem_ops;
    float sum1;
    float sum2;
    int block;
    int left;
    int id;
    int m;

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
    block = dim_M / NUM_CORES;
    left = dim_M % NUM_CORES;
    row_start = id * block + (id < left ? id : left);
    row_end = row_start + block + (id < left ? 1 : 0);
    rem_ops = dim_N % 2;

    m = row_start;
    if (rem_ops) {
        /* loop unroll will have leftovers */
        do {
            mat_vec_mul(mat, vec_x, m, dim_M, dim_N, &sum1, &sum2);
            /* leftovers */
            sum1 += mat[m * dim_N + (dim_N - 1)] * vec_x[dim_N - 1];
            dst[m] = alpha * (sum1 + sum2) + beta * vec_y[m];
            m++;
        } while (m < row_end);
    } else {
        /* loop unroll will NOT have leftovers */
        do {
            mat_vec_mul(mat, vec_x, m, dim_M, dim_N, &sum1, &sum2);
            dst[m] = alpha * (sum1 + sum2) + beta * vec_y[m];
            m++;
        } while (m < row_end);
    }

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}

#else   /* CLUSTER */

int linalg_gemv_serial(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N)
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

    for (int m = 0; m < dim_M; m++) {
        sum = 0;
        for (int n = 0; n < dim_N; n++)
            sum += mat[m * dim_N + n] * vec_x[n];
        dst[m] = alpha * sum + beta * vec_y[m];
    }

    return 0;
}

#endif  /* CLUSTER */

__attribute__((noinline)) int linalg_gemv(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = linalg_gemv_parallel(mat, vec_x, vec_y, alpha, beta, dst, dim_M, dim_N);
#else   /* CLUSTER */
    ret = linalg_gemv_serial(mat, vec_x, vec_y, alpha, beta, dst, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
