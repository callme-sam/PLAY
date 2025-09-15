#include "play.h"

#include "pmsis.h"

#ifdef  CLUSTER

int vector_memcpy_parallel(const float *src, float *dst, const int len)
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

        dst[idx1] = src1;
        dst[idx2] = src2;

        i += 2;
        op++;
    } while (op < tot_ops);

    if (rem_ops)
        dst[end - 1] = src[end - 1];

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}

#else   /* CLUSTER */

int vector_memcpy_serial(const float *src, float *dst, const int len)
{
    for (int i = 0; i < len; i++)
        dst[i] = src[i];

    return 0;
}

#endif  /* CLUSTER */

__attribute__((noinline)) int vector_memcpy(const float *src, float *dst, const int len)
{
    int ret;

#ifdef  CLUSTER
    ret = vector_memcpy_parallel(src, dst, len);
#else   /* CLUSTER */
    ret = vector_memcpy_serial(src, dst, len);
#endif  /* CLUSTER */

    return ret;
}
