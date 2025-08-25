#include "play.h"

#include "pmsis.h"

#ifdef CLUSTER

static int vector_scale_parallel(const float *src, const float val, float *dst, const int len)
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

    for (int i = start; i < end; i++)
        dst[i] = src[i] * val;

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

int vector_scale(const float *src, const float val, float *dst, const int len)
{
    int ret;

#ifdef CLUSTER
    ret = vector_scale_parallel(src, val, dst, len);
#else   /* CLUSTER */
    ret = vector_scale_serial(src, val, dst, len);
#endif  /* CLUSTER */

    return ret;
}