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

    id = pi_core_id();
    block = len / NUM_CORES;
    left = len % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);

    for (int i = start; i < end; i++)
        vec[i] = val;

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

int vector_set_all(float *vec, const float val, const int len)
{
    int ret;

#ifdef  CLUSTER
    ret = vector_set_all_parallel(vec, val, len);
#else   /* CLUSTER */
    ret = vector_set_all_serial(vec, val, len);
#endif  /* CLUSTER */

    return ret;
}
