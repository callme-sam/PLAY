#if TARGET_IS_SPATZ

#include "../arch_interface.h"
#include "play.h"

#include "snrt.h"

int vector_sub_spatz(const float *src_a, const float *src_b, float *dst, const int len)
{
    int remaining = len;
    size_t vl;

    const float *a = src_a;
    const float *b = src_b;
    float *d = dst;

    while (remaining > 0) {

        asm volatile (
            "vsetvli %0, %1, e32, m1, ta, ma"
            : "=r"(vl)
            : "r"(remaining)
        );

        asm volatile (
            "vle32.v v0, (%0)"
            :: "r"(a)
        );
        asm volatile (
            "vle32.v v1, (%0)"
            :: "r"(b)
        );

        asm volatile (
            "vfsub.vv v2, v0, v1"
        );

        asm volatile (
            "vse32.v v2, (%0)"
            :: "r"(d)
        );

        a += vl;
        b += vl;
        d += vl;

        remaining -= vl;
    }
}

#endif  /* TARGET_IS_SPATZ */
