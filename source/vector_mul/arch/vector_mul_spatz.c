#if TARGET_IS_SPATZ

#include "../arch_interface.h"
#include "play.h"

#include "snrt.h"
#include "printf.h"

int vector_mul_spatz(const float *src_a, const float *src_b, float *dst, const int len)
{
    int start;
    int block;
    int left;
    int end;
    int id;

    size_t cc_avl;
    size_t avl;
    size_t vl;

    const float *a;
    const float *b;
    float *d;

    id = snrt_cluster_core_idx();
    block = len / NUM_CC;
    left = len % NUM_CC;

    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);
    cc_avl = end - start;
    avl = cc_avl;

    a = src_a + start;
    b = src_b + start;
    d = dst + start;

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m1, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vle32.v v0, (%0)" :: "r"(a));
        asm volatile ("vle32.v v1, (%0)" :: "r"(b));

        asm volatile("vfmul.vv v2, v0, v1");

        asm volatile("vse32.v v2, (%0)" :: "r"(d));

        a += vl;
        b += vl;
        d += vl;
    }

#if NUM_CC > 1
    snrt_cluster_hw_barrier();
#endif

return 0;

}

#endif  /* TARGET_IS_SPATZ */
