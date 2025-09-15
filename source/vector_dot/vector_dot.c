#include "play.h"

#include "pmsis.h"

#ifdef CLUSTER

PI_L1 float local_dot[NUM_CORES];

int vector_dot_parallel(const float *src_a, const float *src_b, float *dst, const int len)
{
    float dot_tmp1;
    float dot_tmp2;
    int rem_ops;
    int tot_ops;
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
    dot_tmp1 = 0;
    dot_tmp2 = 0;
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

        dot_tmp1 += a1 * b1;
        dot_tmp2 += a2 * b2;
        i += 2;
        op++;
    } while (op < tot_ops);

    if (rem_ops)
        dot_tmp1 += src_a[end - 1] * src_b[end - 1];

    /* Only master core computes final dot prod */
    local_dot[id] = dot_tmp1 + dot_tmp2;

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    if (id != 0)
        goto exit;

    *dst = 0.0f;
    for (i = 0; i < NUM_CORES; i++)
        *dst += local_dot[i];

exit:

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}

#else   /* CLUSTER */

int vector_dot_serial(const float *src_a, const float *src_b, float *dst, const int len)
{
    *dst = 0.0f;
    for (int i = 0; i < len; i++)
        *dst += src_a[i] * src_b[i];

    return 0;
}

#endif  /* CLUSTER */

__attribute__((noinline)) int vector_dot(const float *src_a, const float *src_b, float *dst, const int len)
{
    int ret;

#ifdef CLUSTER
    ret = vector_dot_parallel(src_a, src_b, dst, len);
#else   /* CLUSTER */
    ret = vector_dot_serial(src_a, src_b, dst, len);
#endif  /* CLUSTER */

    return ret;
}
