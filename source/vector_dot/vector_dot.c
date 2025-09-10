#include "play.h"

#include "pmsis.h"

#ifdef CLUSTER

PI_L1 float local_dot[NUM_CORES];

int vector_dot_parallel(const float *src_a, const float *src_b, float *dst, const int len)
{
    float dot_tmp1;
    float dot_tmp2;
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
    dot_tmp1 = 0;
    end = start + block + (id < left ? 1 : 0);
    dot_tmp2 = 0;

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

        dot_tmp1 += a1 * b1;
        dot_tmp2 += a2 * b2;
    }

    if (i < end)
        dot_tmp1 += src_a[i] * src_b[i];

    /* Only master core computes final dot prod */
    local_dot[id] = dot_tmp1 + dot_tmp2;
    pi_cl_team_barrier();
    if (id != 0)
        goto exit;

    *dst = 0.0f;
    for (int i = 0; i < NUM_CORES; i++)
        *dst += local_dot[i];

exit:
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
