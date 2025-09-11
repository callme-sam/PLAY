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

#if 0
    /* for + unroll */
    /* 1C - cycl: - stall: - tcdm: - ipc: */
    /* 8C - cycl: - stall: - tcdm: - ipc: */
    for (int m = row_start; m < row_end; m++) {
        for (int p = 0; p < dim_P; p++) {
            float sum1 = 0;
            float sum2 = 0;
            for (int n = 0; (n + 1) < dim_N; n += 2) {
                float src_a1, src_a2;
                float src_b1, src_b2;

                src_a1 = src_a[m * dim_N + n];
                src_a2 = src_a[m * dim_N + (n + 1)];
                src_b1 = src_b[n * dim_P + p];
                src_b2 = src_b[(n + 1) * dim_P + p];

                sum1 += src_a1 * src_b1;
                sum2 += src_a2 * src_b2;
            }
            dst[m * dim_P + p] = sum1 + sum2;
        }
    }

    if (dim_N % 2) {
        for (int m = row_start; m < row_end; m++) {
            for (int p = 0; p < dim_P; p++) {
                float a;
                float b;

                a = src_a[m * dim_N + (dim_N - 1)];
                b = src_b[(dim_N - 1) * dim_P + p];

                dst[m * dim_P + p] += a * b;
            }
        }
    }
#endif

#if 0
    /* do-while + unroll */
    /* 1C - cycl: - stall: - tcdm: - ipc: */
    /* 8C - cycl: - stall: - tcdm: - ipc: */
    int m, n, p;
    float sum1, sum2;

    m = row_start;
    do {
        p = 0;
        do {
            sum1 = 0;
            sum2 = 0;
            n = 0;
            do {
                float src_a1, src_a2;
                float src_b1, src_b2;

                src_a1 = src_a[m * dim_N + n];
                src_a2 = src_a[m * dim_N + (n + 1)];
                src_b1 = src_b[n * dim_P + p];
                src_b2 = src_b[(n + 1) * dim_P + p];

                sum1 += src_a1 * src_b1;
                sum2 += src_a2 * src_b2;

                n += 2;
            } while ((n + 1) < dim_N);

            dst[m * dim_P + p] = sum1 + sum2;
            p++;
        } while (p < dim_P);

        m++;
    } while (m < row_end);

    if (dim_N % 2) {
        m = row_start;
        do {
            p = 0;
            do {
                float a;
                float b;

                a = src_a[m * dim_N + (dim_N - 1)];
                b = src_b[(dim_N - 1) * dim_P + p];

                dst[m * dim_P + p] += a * b;
                p++;
            } while(p < dim_P);

            m++;
        } while(m < row_end);
    }

#endif

#if 1
    /* do-while single step + unroll */
    /* 1C - cycl: - stall: - tcdm: - ipc: */
    /* 8C - cycl: - stall: - tcdm: - ipc: */
    int num_ops;
    int rem_ops;
    int m, n, p;
    float sum1, sum2;


    rem_ops = dim_N % 2;
    m = row_start;
    do {
        p = 0;
        do {
            num_ops = dim_N / 2;
            sum1 = 0;
            sum2 = 0;
            n = 0;
            do {
                float src_a1, src_a2;
                float src_b1, src_b2;

                src_a1 = src_a[m * dim_N + n];
                src_a2 = src_a[m * dim_N + (n + 1)];
                src_b1 = src_b[n * dim_P + p];
                src_b2 = src_b[(n + 1) * dim_P + p];

                sum1 += src_a1 * src_b1;
                sum2 += src_a2 * src_b2;

                n += 2;
                num_ops--;
            } while (num_ops > 0);

            dst[m * dim_P + p] = sum1 + sum2;
            p++;
        } while (p < dim_P);

        m++;
    } while (m < row_end);

    if (rem_ops) {
        m = row_start;
        do {
            p = 0;
            do {
                float a;
                float b;

                a = src_a[m * dim_N + (dim_N - 1)];
                b = src_b[(dim_N - 1) * dim_P + p];

                dst[m * dim_P + p] += a * b;
                p++;
            } while (p < dim_P);
            m++;
        } while (m < row_end);
    }
#endif

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

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

__attribute__((noinline))int matrix_mul(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    int ret;

#ifdef  CLUSTER
    ret = matrix_mul_parallel(src_a, src_b, dst, dim_M, dim_N, dim_P);
#else   /* CLUSTER */
    ret = matrix_mul_serial(src_a, src_b, dst, dim_M, dim_N, dim_P);
#endif  /* CLUSTER */

    return ret;
}
