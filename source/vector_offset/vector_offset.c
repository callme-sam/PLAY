#include "play.h"

#include "pmsis.h"

#ifdef CLUSTER

static int vector_offset_parallel(const float *src, const float offset, float *dst, const int len)
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

    for (int i = start; (i + 1) < end; i += 2) {
        int idx1, idx2;
        float src1, src2;

        idx1 = i;
        idx2 = i + 1;

        src1 = src[idx1];
        src2 = src[idx2];

        dst[idx1] = src1 + offset;
        dst[idx2] = src2 + offset;
    }

    if (i < end)
        dst[i] = src[i] + offset;

    return 0;
}

#else   /* CLUSTER */

static int vector_offset_serial(const float *src, const float offset, float *dst, const int len)
{
    for (int i = 0; i < len; i++)
        dst[i] = src[i] + offset;

    return 0;
}

#endif  /* CLUSTER */

__attribute__((noinline)) int vector_offset(const float *src, const float offset, float *dst, const int len)
{
    int ret;

#ifdef CLUSTER
    ret = vector_offset_parallel(src, offset, dst, len);
#else   /* CLUSTER */
    ret = vector_offset_serial(src, offset, dst, len);
#endif  /* CLUSTER */

    return ret;
}
