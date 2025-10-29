#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int vector_scale_spatz_serial(const float *src, const float val, float *dst, const int len)
{
    size_t avl;
    size_t vl;

    const float *p_src;
    const float *p_dst;

    avl = len;
    p_src = src;
    p_dst = dst;

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vle32.v v0, (%0)" :: "r"(p_src));

        asm volatile("vfmul.vf v8, v0, %0" :: "f"(val));

        asm volatile("vse32.v v8, (%0)" :: "r"(p_dst));

        p_src += vl;
        p_dst += vl;
    }

    return 0;
}

int vector_scale_impl(const float *src, const float val, float *dst, const int len)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = vector_scale_spatz_serial(src, val, dst, len);
#endif

    return ret;
}
