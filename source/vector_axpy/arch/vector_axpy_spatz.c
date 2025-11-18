#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int vector_axpy_spatz_serial(const float *src_a, const float *src_b, const float alpha, float *dst, const int len)
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
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vle32.v v0, (%0)" :: "r"(a));
        asm volatile ("vle32.v v8, (%0)" :: "r"(b));

#if 1
#if 1
        /* 971 cycl */
        asm volatile ("vfmul.vf v16, v0, %0" :: "f"(alpha));
        asm volatile ("vfadd.vv v24, v16, v8");
        asm volatile ("vse32.v v24, (%0)" :: "r"(d));
#else
        /* 1147 cycl */
        asm volatile ("vfmul.vf v0, v0, %0" :: "f"(alpha));
        asm volatile ("vfadd.vv v0, v0, v8");
        asm volatile ("vse32.v v0, (%0)" :: "r"(d));
#endif
#else
        /* 1147 cycl */
        asm volatile ("vfmacc.vf v8, %0, v0" ::"f"(alpha));
        asm volatile ("vse32.v v8, (%0)" :: "r"(d));
#endif

        a += vl;
        b += vl;
        d += vl;
    }

    return 0;
}

int vector_axpy_impl(const float *src_a, const float *src_b, const float alpha, float *dst, const int len)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = vector_axpy_spatz_serial(src_a, src_b, alpha, dst, len);
#endif

    return ret;
}
