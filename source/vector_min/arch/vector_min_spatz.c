#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int vector_min_spatz_serial(const float *src, float *min, const int len)
{
    const float *p_src;
    size_t avl;
    size_t vl;

    p_src = src;
    avl = len;

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vfmv.s.f v0, %0" :: "f"(src[0]));

    do {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
        asm volatile ("vle32.v v8, (%0)" :: "r"(p_src));
        asm volatile ("vfredmin.vs v0, v8, v0");

        p_src += vl;
        avl -= vl;
    } while (avl > 0);

    asm volatile ("vfmv.f.s %0, v0" : "=f"(*min));

    return 0;
}

int vector_min_impl(const float *src, float *min, const int len)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = vector_min_spatz_serial(src, min, len);
#endif

    return ret;
}
