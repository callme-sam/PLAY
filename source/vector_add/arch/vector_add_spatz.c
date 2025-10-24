#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int vector_add_spatz_serial(const float *src_a, const float *src_b, float *dst, const int len)
{
    size_t avl;
    size_t vl;

    const float *a;
    const float *b;
    float *d;

    avl = len;
    a = src_a;
    b = src_b;
    d = dst;

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m1, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vle32.v v0, (%0)" :: "r"(a));
        asm volatile ("vle32.v v1, (%0)" :: "r"(b));

        asm volatile("vfadd.vv v2, v0, v1");

        asm volatile("vse32.v v2, (%0)" :: "r"(d));

        a += vl;
        b += vl;
        d += vl;
    }

    return 0;
}

int vector_add_impl(const float *src_a, const float *src_b, float *dst, const int len)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = vector_add_spatz_serial(src_a, src_b, dst, len);
#endif

    return ret;
}
