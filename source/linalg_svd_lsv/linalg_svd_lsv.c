#include "play.h"

#include "pmsis.h"

static PI_L1 float ONE_f = 1;
static PI_L1 float EPSILON = 1e-12;

#ifdef  CLUSTER

#if 0
/* noopt */
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

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
/* for-unroll */
int linalg_svd_lsv_parallel(const float *src, float *mat_V, float *vec_S, float *dst, const int dim_M, const int dim_N)
{
    float sum1;
    float sum2;
    int block;
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
        float s, s_inv;

        s = vec_S[k];

        if (s < EPSILON) {
            for (int m = 0; (m + 1) < dim_M; m++) {
                dst[m * dim_N + k] = 0;
                dst[(m + 1) * dim_N + k] = 0;
            }

            if (dim_M % 2)
                dst[(dim_M - 1) * dim_N + k] = 0;

            continue;
        } else {
            s_inv = 1.0f / s;
        }

        for (int m = 0; m < dim_M; m++) {
            sum1 = 0;
            sum2 = 0;

            for (int n = 0; (n + 1) < dim_N; n += 2) {
                float src1, src2;
                float v1, v2;

                src1 = src[m * dim_N + n];
                src2 = src[m * dim_N + (n + 1)];
                v1 = mat_V[n * dim_N + k];
                v2 = mat_V[(n + 1) * dim_N + k];

                sum1 += src1 * v1;
                sum2 += src2 * v2;
            }

            if (dim_N % 2)
                sum1 += src[m * dim_N + (dim_N - 1)] * mat_V[(dim_N - 1) * dim_N + k];

            dst[m * dim_N + k] = (sum1 + sum2) * s_inv;
        }
    }

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 1
/* while-unroll */
int linalg_svd_lsv_parallel(const float *src, float *mat_V, float *vec_S, float *dst, const int dim_M, const int dim_N)
{
    int tot_ops_M;
    int rem_ops_M;
    int tot_ops_N;
    int rem_ops_N;
    int k, m, n;
    float sum1;
    float sum2;
    int block;
    int start;
    int left;
    int end;
    int id;
    int op;

    id = pi_core_id();
    block = dim_N / NUM_CORES;
    left = dim_N % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);

    tot_ops_M = dim_M / 2;
    rem_ops_M = dim_M % 2;
    tot_ops_N = dim_N / 2;
    rem_ops_N = dim_N % 2;

    k = start;
    do {
        float s, s_inv;
        s = vec_S[k];

        if (s < EPSILON) {
            op = 0;
            m = 0;
            do {
                dst[m * dim_N + k] = 0;
                dst[(m + 1) * dim_N + k] = 0;

                m +=  2;
                op++;
            } while (op < tot_ops_M);

            if (rem_ops_M)
                dst[(dim_M - 1) * dim_N + k] = 0;

            continue;
        } else {
            s_inv = ONE_f / s;
        }

        m = 0;
        do {
            sum1 = 0;
            sum2 = 0;

            n = 0;
            op = 0;
            do {
                float src1, src2;
                float v1, v2;

                src1 = src[m * dim_N + n];
                src2 = src[m * dim_N + (n + 1)];
                v1 = mat_V[n * dim_N + k];
                v2 = mat_V[(n + 1) * dim_N + k];

                sum1 += src1 * v1;
                sum2 += src2 * v2;

                n += 2;
                op++;
            } while (op < tot_ops_N);

            if (rem_ops_N)
                sum1 += src[m * dim_N + (dim_N - 1)] * mat_V[(dim_N - 1) * dim_N + k];

            dst[m * dim_N + k] = (sum1 + sum2) * s_inv;
            m++;
        } while (m < dim_M);

        k++;
    } while (k < end);

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}
#endif

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

__attribute__((noinline)) int linalg_svd_lsv(const float *src, float *mat_V, float *vec_S, float *dst, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = linalg_svd_lsv_parallel(src, mat_V, vec_S, dst, dim_M, dim_N);
#else   /* CLUSTER */
    ret = linalg_svd_lsv_serial(src, mat_V, vec_S, dst, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
