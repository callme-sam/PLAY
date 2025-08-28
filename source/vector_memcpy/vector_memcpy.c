#include "play.h"

#include "pmsis.h"

#ifdef  CLUSTER

int vector_memcpy_parallel(const float *src, float *dst, const int len)
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
        dst[i] = src[i];

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

int vector_memcpy(const float *src, float *dst, const int len)
{
    int ret;

#ifdef  CLUSTER
    ret = vector_memcpy_parallel(src, dst, len);
#else   /* CLUSTER */
    ret = vector_memcpy_serial(src, dst, len);
#endif  /* CLUSTER */

    return ret;
}
