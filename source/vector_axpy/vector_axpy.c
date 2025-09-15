#include "play.h"

#include "pmsis.h"

#ifdef  CLUSTER

#if 1
/* for-unroll */
static int vector_axpy_parallel(const float *src_a, const float *src_b, const float alpha, float *dst, const int len)
{
    int block;
    int start;
    int left;
    int end;
    int id;
    int i;

    id = pi_core_id();
    block = len / NUM_CORES;
    left = len % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);

    for (i = start; (i + 1) < end; i += 2) {
        int idx1, idx2;
        float a1, a2;
        float b1, b2;

        idx1 = i;
        idx2 = i + 1;
        a1 = src_a[idx1];
        b1 = src_b[idx1];
        a2 = src_a[idx2];
        b2 = src_b[idx2];

        dst[idx1] = a1 * alpha + b1;
        dst[idx2] = a2 * alpha + b2;
    }

    if (i < end)
        dst[i] = src_a[i] * alpha + src_b[i];

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}
#endif

#if 0
/* while-unroll-singlestep */
static int vector_axpy_parallel(const float *src_a, const float *src_b, const float alpha, float *dst, const int len)
{
    int tot_ops;
    int rem_ops;
    int block;
    int start;
    int left;
    int end;
    int id;
    int op;
    int i;

    id = pi_core_id();
    block = len / NUM_CORES;
    left = len % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);
    tot_ops = (end - start) / 2;
    rem_ops = tot_ops % 2;
    i = start;
    op = 0;

    do {
        int idx1, idx2;
        float a1, a2;
        float b1, b2;

        idx1 = i;
        idx2 = i + 1;
        a1 = src_a[idx1];
        b1 = src_b[idx1];
        a2 = src_a[idx2];
        b2 = src_b[idx2];

        dst[idx1] = a1 * alpha + b1;
        dst[idx2] = a2 * alpha + b2;

        i += 2;
        op++;
    } while (op < tot_ops);

    if (rem_ops)
        dst[end - 1] = src_a[end - 1] * alpha + src_b[end - 1];

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}
#endif

#else   /* CLUSTER */

static int vector_axpy_serial(const float *src_a, const float *src_b, const float alpha, float *dst, const int len)
{
    for (int i = 0; i < len; i++)
        dst[i] = src_a[i] * alpha + src_b[i];

    return 0;
}

#endif  /* CLUSTER */

int vector_axpy(const float *src_a, const float *src_b, const float alpha, float *dst, const int len)
{
    int ret;

#ifdef  CLUSTER
    ret = vector_axpy_parallel(src_a, src_b, alpha, dst, len);
#else   /* CLUSTER */
    ret = vector_axpy_serial(src_a, src_b, alpha, dst, len);
#endif  /* CLUSTER */

    return ret;
}
