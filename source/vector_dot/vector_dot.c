#include "play.h"

#include "pmsis.h"

#ifdef CLUSTER

PI_L1 float local_dot[NUM_CORES];

int vector_dot_parallel(const float *src_a, const float *src_b, float *dst, const int len)
{
    int block;
    int start;
    int left;
    int end;
    int id;

    id = pi_core_id();
    block = len / NUM_CORES;
    left = len % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);

    local_dot[id] = 0.0f;
    for (int i = start; i < end; i++)
        local_dot[id] += src_a[i] * src_b[i];

    /* Only master core computes final dot prod */
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

int vector_dot(const float *src_a, const float *src_b, float *dst, const int len)
{
    int ret;

#ifdef CLUSTER
    ret = vector_dot_parallel(src_a, src_b, dst, len);
#else   /* CLUSTER */
    ret = vector_dot_serial(src_a, src_b, dst, len);
#endif  /* CLUSTER */

    return ret;
}