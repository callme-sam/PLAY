#include "play.h"

#include "pmsis.h"

#ifdef CLUSTER

static int vector_scale_parallel(const float *src, const float val, float *dst, const int len)
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
        float src1, src2;

        idx1 = i;
        idx2 = i + 1;

        src1 = src[idx1];
        src2 = src[idx2];

        dst[idx1] = src1 * val;
        dst[idx2] = src2 * val;

        i += 2;
        op++;
    } while (op < tot_ops);

    if (rem_ops)
        dst[end - 1] = src[end - 1] * val;

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}

#else   /* CLUSTER */

static int vector_scale_serial(const float *src, const float val, float *dst, const int len)
{
    for (int i = 0; i < len; i++)
        dst[i] = src[i] * val;

    return 0;
}

#endif  /* CLUSTER */

__attribute__((noinline)) int vector_scale(const float *src, const float val, float *dst, const int len)
{
    int ret;

#ifdef CLUSTER
    ret = vector_scale_parallel(src, val, dst, len);
#else   /* CLUSTER */
    ret = vector_scale_serial(src, val, dst, len);
#endif  /* CLUSTER */

    return ret;
}
