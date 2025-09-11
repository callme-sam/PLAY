#include "play.h"

#include "pmsis.h"


#ifdef  CLUSTER

int vector_set_all_parallel(float *vec, const float val, const int len)
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

    for (i = start; (i + 1) < end; i += 2) {
        int idx1, idx2;

        idx1 = i;
        idx2 = i + 1;

        vec[idx1] = val;
        vec[idx2] = val;
    }

    if (i < end)
        vec[i] = val;

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}

#else   /* CLUSTER */

int vector_set_all_serial(float *vec, const float val, const int len)
{
    for (int i = 0; i < len; i++)
        vec[i] = val;

    return 0;
}

#endif  /* CLUSTER */

__attribute__((noinline)) int vector_set_all(float *vec, const float val, const int len)
{
    int ret;

#ifdef  CLUSTER
    ret = vector_set_all_parallel(vec, val, len);
#else   /* CLUSTER */
    ret = vector_set_all_serial(vec, val, len);
#endif  /* CLUSTER */

    return ret;
}
