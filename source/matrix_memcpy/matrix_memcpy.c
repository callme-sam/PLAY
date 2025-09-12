#include "play.h"

#include "pmsis.h"

#ifdef  CLUSTER

#if 0
/* FOR-UNROLL m, n */
int matrix_memcpy_parallel(const float *src, float *dst, const int dim_M, const int dim_N)
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

    for (int m = row_start; m < row_end; m++) {
       for (int n = 0; (n + 1) < dim_N; n += 2) {
            int idx1, idx2;
            float src1, src2;

            idx1 = m * dim_N + n;
            idx2 = m * dim_N + (n + 1);
            src1 = src[idx1];
            src2 = src[idx2];

            dst[idx1] = src1;
            dst[idx2] = src2;
        }
    }

    if (dim_N % 2) {
        for (int m = row_start; m < row_end; m++) {
            dst[m * dim_N + (dim_N - 1)] = src[m * dim_N + (dim_N - 1)];
            m++;
        }
    }

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}
#endif

#if 0
/* FOR-UNROLL-single-step m, n */
int matrix_memcpy_parallel(const float *src, float *dst, const int dim_M, const int dim_N)
{
    int row_start;
    int row_end;
    int num_ops;
    int rem_ops;
    int block;
    int left;
    int id;

    id = pi_core_id();
    block = dim_M / NUM_CORES;
    left = dim_M % NUM_CORES;
    row_start = id * block + (id < left ? id : left);
    row_end = row_start + block + (id < left ? 1 : 0);
    num_ops = dim_N / 2;
    rem_ops = dim_N % 2;

    for (int m = row_start; m < row_end; m++) {
        int n = 0;
       for (int op = 0; op < num_ops; op++) {
            int idx1, idx2;
            float src1, src2;

            idx1 = m * dim_N + n;
            idx2 = m * dim_N + (n + 1);
            src1 = src[idx1];
            src2 = src[idx2];

            dst[idx1] = src1;
            dst[idx2] = src2;
            n += 2;
        }
    }

    if (rem_ops) {
        for (int m = row_start; m < row_end; m++) {
            dst[m * dim_N + (dim_N - 1)] = src[m * dim_N + (dim_N - 1)];
            m++;
        }
    }

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}
#endif

#if 0
/* DO-WHILE-UNROLL */
int matrix_memcpy_parallel(const float *src, float *dst, const int dim_M, const int dim_N)
{
    int row_start;
    int row_end;
    int block;
    int left;
    int m, n;
    int id;

    id = pi_core_id();
    block = dim_M / NUM_CORES;
    left = dim_M % NUM_CORES;
    row_start = id * block + (id < left ? id : left);
    row_end = row_start + block + (id < left ? 1 : 0);

    m = row_start;
    do {
        n = 0;
        do {
            int idx1, idx2;
            float src1, src2;

            idx1 = m * dim_N + n;
            idx2 = m * dim_N + (n + 1);
            src1 = src[idx1];
            src2 = src[idx2];

            dst[idx1] = src1;
            dst[idx2] = src2;
            n += 2;
        } while ((n + 1) < dim_N);
        m++;
    } while (m < row_end);

    if (dim_N % 2) {
        m = row_start;
        do {
            dst[m * dim_N + (dim_N - 1)] = src[m * dim_N + (dim_N - 1)];
            m++;
        } while (m < row_end);
    }

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}
#endif

#if 1
/* DO-WHILE-UNROLL-singlestep */
int matrix_memcpy_parallel(const float *src, float *dst, const int dim_M, const int dim_N)
{
    int row_start;
    int row_end;
    int num_ops;
    int rem_ops;
    int block;
    int left;
    int m, n;
    int ops;
    int id;

    id = pi_core_id();
    block = dim_M / NUM_CORES;
    left = dim_M % NUM_CORES;
    row_start = id * block + (id < left ? id : left);
    row_end = row_start + block + (id < left ? 1 : 0);
    num_ops = dim_N / 2;
    rem_ops = dim_N % 2;

    m = row_start;
    do {
        n = 0;
        ops = 0;
        do {
            int idx1, idx2;
            float src1, src2;

            idx1 = m * dim_N + n;
            idx2 = m * dim_N + (n + 1);
            src1 = src[idx1];
            src2 = src[idx2];

            dst[idx1] = src1;
            dst[idx2] = src2;
            n += 2;
            ops++;
        } while (ops < num_ops);
        m++;
    } while (m < row_end);

    if (rem_ops) {
        m = row_start;
        do {
            dst[m * dim_N + (dim_N - 1)] = src[m * dim_N + (dim_N - 1)];
            m++;
        } while (m < row_end);
    }

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}
#endif

#else   /* CLUSTER */

int matrix_memcpy_serial(const float *src, float *dst, const int dim_M, const int dim_N)
{
    for (int m = 0; m < dim_M; m++)
        for (int n = 0; n < dim_N; n++)
            dst[m * dim_N + n] = src[m * dim_N + n];

    return 0;
}

#endif  /* CLUSTER */

__attribute__((noinline)) int matrix_memcpy(const float *src, float *dst, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = matrix_memcpy_parallel(src, dst, dim_M, dim_N);
#else   /* CLUSTER */
    ret = matrix_memcpy_serial(src, dst, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
