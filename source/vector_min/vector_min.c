#include "play.h"

#include "pmsis.h"

#ifdef CLUSTER

PI_L1 float local_min[NUM_CORES];

static int vector_min_parallel(const float *src, float *min, const int len)
{
    float min_tmp;
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
    min_tmp = src[start];

#if 0
    /* unroll with step-2 */
    /* 1C -- cycl: 12314 - stall: 1027 - ipc: 0.66 */
    /* 8C -- cycl: 1602  - stall: 129  - ipc: 0.66 */
    for (int i = start + 1; (i + 1) < end; i += 2) {
        int idx1, idx2;
        float src1, src2;

        idx1 = i;
        idx2 = i + 1;
        src1 = src[idx1];
        src2 = src[idx2];

        if (src1 < src2) {
            if (src1 < min_tmp)
                min_tmp = src1;
        } else if (src2 < min_tmp) {
            min_tmp = src2;
        }
    }


    if (i < end) {
        if (src[i] < min_tmp)
        min_tmp = src[i];
    }

#endif

#if 1
    /* unroll with step-4 */
    /* cycl: 11819 - stall: 6 - ipc: 0.65 */
    /* cycl: 1567  - stall: 4 - ipc: 0.65 */
    for (i = (start + 1); (i + 3) < end; i += 4) {
        int idx1, idx2, idx3, idx4;
        float src1, src2, src3, src4;

        idx1 = i;
        idx2 = i + 1;
        idx3 = i + 2;
        idx4 = i + 3;

        src1 = src[idx1];
        src2 = src[idx2];
        src3 = src[idx3];
        src4 = src[idx4];

        if (src1 < src2) {
            if (src1 < min_tmp)
                min_tmp = src1;
        } else if (src2 < min_tmp) {
            min_tmp = src2;
        }

        if (src3 < src4) {
            if (src3 < min_tmp)
                min_tmp = src3;
        } else if (src4 < min_tmp) {
            min_tmp = src4;
        }
    }

    for(; i < end; i++) {
        if (src[i] < min_tmp)
            min_tmp = src[i];
    }
#endif


#if 0
    /* sw pipelining */
    /* cycl: 20508 - stall: 3 - ipc: 0.60 */
    /* cycl: 2609  - stall: 1 - ipc: 0.60 */
    float cur_src, next_src;
    min_tmp = src[start];
    cur_src = src[start];
    for (i = start; (i + 1) < end; i++) {
        next_src = src[i + 1];
        if (cur_src < min_tmp)
            min_tmp = cur_src;

        cur_src = next_src;
    }
#endif

#if 0
    /* sw pipelining + unroll step-2 */
    /* cycl: 13397 - stall: 5 - ipc: 0.76 */
    /* cycl: 1798  - stall: 3 - ipc: 0.75 */
    float src1, src2;
    float nxt_src1, nxt_src2;

    src1 = src[start];
    src2 = src[start + 1];
    min_tmp = src[start];

    for (i = start; (i + 3) < end; i += 2) {
        nxt_src1 = src[i + 2];
        nxt_src2 = src[i + 3];

        if (src1 < src2) {
            if (src1 < min_tmp)
                min_tmp = src1;
        } else if (src2 < min_tmp) {
            min_tmp = src2;
        }

        src1 = nxt_src1;
        src2 = nxt_src2;
    }

    for(; i < end; i++) {
        if (src[i] < min_tmp)
            min_tmp = src[i];
    }
#endif

    local_min[id] = min_tmp;

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

__attribute__((noinline)) int vector_min(const float *src, float *min, const int len)
{
    int ret;

#ifdef  CLUSTER
    ret = vector_min_parallel(src, min, len);
#else   /* CLUSTER */
    ret = vector_min_serial(src, min, len);
#endif  /* CLUSTER */

    return ret;
}
