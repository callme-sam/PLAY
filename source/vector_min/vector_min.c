#include "play.h"

#include "pmsis.h"

#ifdef CLUSTER

PI_L1 float local_min[NUM_CORES];

static int vector_min_parallel(const float *src, float *min, const int len)
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

    local_min[id] = src[start];
    for (int i = start + 1; i < end; i++) {
        if (src[i] < local_min[id])
            local_min[id] = src[i];
    }

    pi_cl_team_barrier();
    if (id != 0) {
        /* Only master core finds absolute minimum */
        goto exit;
    }

    *min = local_min[0];
    for (int i = 1; i < NUM_CORES; i++) {
        if (local_min[i] < *min)
            *min = local_min[i];
    }

exit:
    return 0;
}

#else   /* CLUSTER */

static int vector_min_serial(const float *src, float *min, const int len)
{
    *min = src[0];
    for (int i = 1; i < len; i++) {
        if (src[i] < *min)
            *min = src[i];
    }

    return 0;
}

#endif  /* CLUSTER */

int vector_min(const float *src, float *min, const int len)
{
    int ret;

#ifdef  CLUSTER
    ret = vector_min_parallel(src, min, len);
#else   /* CLUSTER */
    ret = vector_min_serial(src, min, len);
#endif  /* CLUSTER */

    return ret;
}