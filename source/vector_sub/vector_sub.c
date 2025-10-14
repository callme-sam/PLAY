#include "play.h"

#ifdef SPATZ
#include "debug.h"
#include "snrt.h"
#else
#include "pmsis.h"
#endif

#ifdef SPATZ

static int vector_sub_vectorial(const float *src_a, const float *src_b, float *dst, const int len)
{
    int remaining = len;
    size_t vl; // Actual number of elements processed in the current iteration

    // Use mutable pointers for iteration
    const float *a = src_a;
    const float *b = src_b;
    float *d = dst;

    while (remaining > 0) {
        // 1. Set Vector Length (vsetvli):
        // Set 'vl' (Vector Length) to the minimum of 'remaining' and VLMAX.
        // e32: 32-bit elements (float)
        // m1: Vector register group multiplier
        asm volatile (
            "vsetvli %0, %1, e32, m1, ta, ma"
            : "=r"(vl)          // %0: Output actual VL to C variable 'vl'
            : "r"(remaining)    // %1: Input 'remaining' length
        );

        // 2. Vector Loads (vle32.v): Load vl elements from addresses a and b.
        asm volatile (
            "vle32.v v0, (%0)"
            :: "r"(a)
        );
        asm volatile (
            "vle32.v v1, (%0)"
            :: "r"(b)
        );

        // 3. Vector Calculation (vfadd.vv): Floating-point addition: v2 = v0 + v1
        // Note: 'vadd.vv' is for integer addition. 'vfadd.vv' is correct for floats.
        asm volatile (
            "vfsub.vv v2, v0, v1"
        );

        // 4. Vector Store (vse32.v): Store vl elements from v2 to address d.
        asm volatile (
            "vse32.v v2, (%0)"
            :: "r"(d)
        );

        // 5. Update: Move pointers forward by the number of elements processed ('vl').
        a += vl;
        b += vl;
        d += vl;

        // Decrease the remaining count.
        remaining -= vl;
    }

}

#elif CLUSTER

static int vector_sub_parallel(const float *src_a, const float *src_b, float *dst, const int len)
{
    int rem_ops;
    int tot_ops;
    int block;
    int start;
    int left;
    int end;
    int op;
    int id;
    int i;

    id = pi_core_id();
    block = len / NUM_CORES;
    left = len % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);
    tot_ops = (end - start) / 2;
    rem_ops = tot_ops % 2;
    i = start;
    op = 0;

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
        op++;
    } while (op < tot_ops);

    if (rem_ops)
        dst[end - 1] = src_a[end - 1] - src_b[end - 1];

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}

#else   /* SPATZ / CLUSTER */

static int vector_sub_serial(const float *src_a, const float *src_b, float *dst, const int len)
{
    for (int i = 0; i < len; i++)
        dst[i] = src_a[i] - src_b[i];

    return 0;
}

#endif  /* SPATZ / CLUSTER */

__attribute__((noinline)) int vector_sub(const float *src_a, const float *src_b, float *dst, const int len)
{
    int ret;

#ifdef  SPATZ
    ret = vector_sub_vectorial(src_a, src_b, dst, len);
#elif   CLUSTER
    ret = vector_sub_parallel(src_a, src_b, dst, len);
#else   /* SPATZ / CLUSTER */
    ret = vector_sub_serial(src_a, src_b, dst, len);
#endif  /* SPATZ / CLUSTER */

    return ret;
}
