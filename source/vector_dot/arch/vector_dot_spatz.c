#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"
#include "printf.h"

static int vector_dot_spatz_serial(const float *src_a, const float *src_b, float *dst, const int len)
{
    const float *a;
    const float *b;

    size_t original_avl;
    size_t avl;
    size_t vl;

    original_avl = len;
    avl = len;

    a = src_a;
    b = src_b;

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));
    asm volatile ("vfmv.v.f v24, %0" :: "f"(0.0f));

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vle32.v v8, (%0)" :: "r"(a));
        asm volatile ("vle32.v v16, (%0)" :: "r"(b));

        asm volatile ("vfmacc.vv v24, v8, v16");

        a += vl;
        b += vl;
    }

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(original_avl));
    asm volatile ("vfredsum.vs v0, v24, v0");
    asm volatile ("vfmv.f.s %0, v0" : "=f"(*dst));

    return 0;
}


int vector_dot_impl(const float *src_a, const float *src_b, float *dst, const int len)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = vector_dot_spatz_serial(src_a, src_b, dst, len);
#endif

    return ret;
}
