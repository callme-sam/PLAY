#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int vector_offset_spatz_serial(const float *src, const float offset, float *dst, const int len)
{
    size_t avl;
    size_t vl;

    const float *p_src;
    float *p_dst;

    avl = len;
    p_src = src;
    p_dst = dst;

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vle32.v v0, (%0)" :: "r"(p_src));

        asm volatile ("vfadd.vf v8, v0, %0" :: "f"(offset));

        asm volatile ("vse32.v v8, (%0)" :: "r"(p_dst));

        p_src += vl;
        p_dst += vl;
    }

    return 0;
}

int vector_offset_impl(const float *src, const float offset, float *dst, const int len)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = vector_offset_spatz_serial(src, offset, dst, len);
#endif

    return ret;
}
