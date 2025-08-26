#include "play.h"

#include "pmsis.h"

#ifdef  CLUSTER

static int vector_axpy_parallel(const float *src_a, const float *src_b, const float alpha, float *dst, const int len)
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
        dst[i] = src_a[i] * alpha + src_b[i];

    return 0;
}

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
