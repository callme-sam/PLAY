#include "play.h"

#include "pmsis.h"

#ifdef CLUSTER

int vector_sub_for(const float *src_a, const float *src_b, float *dst, const int len)
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

    for (int i = start; i < end; i++) {
        dst[i] = src_a[i] - src_b[i];
    }

    return 0;
}

int vector_sub_for_unroll(const float *src_a, const float *src_b, float *dst, const int len)
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

    for (i = start; (i + 1) < end; i+=2) {
        int idx1, idx2;
        float a1, a2;
        float b1, b2;

        idx1 = i;
        idx2 = i + 1;
        a1 = src_a[idx1];
        b1 = src_b[idx1];
        a2 = src_a[idx2];
        b2 = src_b[idx2];

        dst[idx1] = a1 - b1;
        dst[idx2] = a2 - b2;
    }

    if (i < end)
        dst[i] = src_a[i] - src_b[i];

    return 0;
}

int vector_sub_for_interleave(const float *src_a, const float *src_b, float *dst, const int len)
{
    int left;
    int ops;
    int end;
    int id;
    int i;

    id = pi_core_id();
    left = len % NUM_CORES;
    ops = len / NUM_CORES + (id < left ? 1 : 0);
    end = ops * NUM_CORES;

    for (i = id; i < end; i += NUM_CORES) {
        dst[i] = src_a[i] - src_b[i];
    }

    return 0;
}

int vector_sub_for_both(const float *src_a, const float *src_b, float *dst, const int len)
{
    int left;
    int ops;
    int end;
    int id;
    int i;

    id = pi_core_id();
    left = len % NUM_CORES;
    ops = len / NUM_CORES + (id < left ? 1 : 0);
    end = ops * NUM_CORES;

    for (i = id; (i + NUM_CORES) < end; i += NUM_CORES * 2) {
        int idx1, idx2;
        float a1, a2;
        float b1, b2;

        idx1 = i;
        idx2 = i + NUM_CORES;
        a1 = src_a[idx1];
        b1 = src_b[idx1];
        a2 = src_a[idx2];
        b2 = src_b[idx2];

        dst[idx1] = a1 - b1;
        dst[idx2] = a2 - b2;
    }

    if (i < end)
        dst[i] = src_a[i] - src_b[i];

    return 0;
}

int vector_sub_while(const float *src_a, const float *src_b, float *dst, const int len)
{
    int block;
    int start;
    int left;
    int cycl;
    int end;
    int ops;
    int id;
    int i;

    if (len <= 0)
        return 0;

    id = pi_core_id();
    block = len / NUM_CORES;
    left = len % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);

    ops = end - start;
    i = start;

    do {
        dst[i] = src_a[i] - src_b[i];
        i++;
        ops--;
    } while(ops > 0);

    return 0;
}

int vector_sub_while_unroll(const float *src_a, const float *src_b, float *dst, const int len)
{
    int block;
    int start;
    int left;
    int cycl;
    int end;
    int rem;
    int ops;
    int id;
    int i;

    if (len <= 0)
        return 0;

    id = pi_core_id();
    block = len / NUM_CORES;
    left = len % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);

    ops = end - start;
    cycl = ops / 2;
    rem = ops % 2;
    i =  start;

    do {
        int idx1, idx2;
        float a1, a2;
        float b1, b2;

        idx1 = i;
        idx2 = i + 1;

        a1 = src_a[idx1];
        b1 = src_b[idx1];

        a2 = src_a[idx2];
        b2 = src_b[idx2];

        dst[idx1] = a1 - b1;
        dst[idx2] = a2 - b2;

        i += 2;
        cycl--;
    } while(cycl > 0);

    if (rem)
        dst[i] = src_a[i] - src_b[i];

    return 0;
}

int vector_sub_while_interleave(const float *src_a, const float *src_b, float *dst, const int len)
{
    int left;
    int ops;
    int end;
    int id;
    int i;

    if (len <= 0)
        return 0;

    id = pi_core_id();
    left = len % NUM_CORES;
    ops = len / NUM_CORES + (id < left ? 1 : 0);
    end = ops * NUM_CORES;
    i = id;

    do {
        dst[i] = src_a[i] - src_b[i];
        i += NUM_CORES;
        ops--;
    } while (ops > 0);

    return 0;
}

int vector_sub_while_both(const float *src_a, const float *src_b, float *dst, const int len)
{
    int left;
    int cycl;
    int ops;
    int end;
    int rem;
    int id;
    int i;

    if (len <= 0)
        return 0;

    id = pi_core_id();
    left = len % NUM_CORES;
    ops = len / NUM_CORES + (id < left ? 1 : 0);
    end = ops * NUM_CORES;

    cycl = ops / 2;
    rem = ops % 2;
    i = id;

    do {
        int idx1, idx2;
        float a1, a2;
        float b1, b2;

        idx1 = i;
        idx2 = i + NUM_CORES;

        a1 = src_a[idx1];
        b1 = src_b[idx1];

        a2 = src_a[idx2];
        b2 = src_b[idx2];

        dst[idx1] = a1 - b1;
        dst[idx2] = a2 - b2;

        i += NUM_CORES * 2;
        cycl--;
    } while (cycl > 0);

    if (rem)
        dst[i] = src_a[i] - src_b[i];

    return 0;
}

#else   /* CLUSTER */

static int vector_sub_serial(const float *src_a, const float *src_b, float *dst, const int len)
{
    for (int i = 0; i < len; i++)
        dst[i] = src_a[i] - src_b[i];

    return 0;
}

#endif  /* CLUSTER */

__attribute__ ((noinline)) int vector_sub(const float *src_a, const float *src_b, float *dst, const int len)
{
    int ret;

#ifdef  CLUSTER

#ifdef  FOR

#ifdef  UNROLL
    ret = vector_sub_for_unroll(src_a, src_b, dst, len);
#elif   INTERLEAVE
    ret = vector_sub_for_interleave(src_a, src_b, dst, len);
#elif   BOTH
    ret = vector_sub_for_both(src_a, src_b, dst, len);
#else   /* UNROLL-INTERLEAVE-BOTH */
    ret = vector_sub_for(src_a, src_b, dst, len);
#endif  /* UNROLL-INTERLEAVE-BOTH */

#elif   WHILE /* FOR-WHILE */

#ifdef  UNROLL
    ret = vector_sub_while_unroll(src_a, src_b, dst, len);
#elif   INTERLEAVE
    ret = vector_sub_while_interleave(src_a, src_b, dst, len);
#elif   BOTH
    ret = vector_sub_while_both(src_a, src_b, dst, len);
#else   /* UNROLL-INTERLEAVE-BOTH */
    ret = vector_sub_while(src_a, src_b, dst, len);
#endif  /* UNROLL-INTERLEAVE-BOTH */

#else   /* FOR-WHILE */
    printf("error\n");
#endif  /* FOR-WHILE */


#else   /* CLUSTER */
    ret = vector_sub_serial(src_a, src_b, dst, len);
#endif  /* CLUSTER */

    return ret;
}
