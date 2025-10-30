#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int vector_min_spatz_serial(const float *src, float *min, const int len)
{
    const float *p_src;
    size_t avl;
    size_t vl;

    *min = src[0];
    p_src = src;
    avl = len;

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vle32.v v8, (%0)" :: "r"(p_src));

        asm volatile ("vfredmin.vs v16, v8, v0");
        snrt_cluster_hw_barrier();

#if 0   /* vfmv.f.s not yet supported :S */
        float local_min;
        asm volatile ("vfmv.f.s %0, v16" : "=f"(local_min));
        if (local_min < *min)
            *min = local_min;
#else
        float local_min[vl];
        asm volatile ("vse32.v v16, (%0)" :: "r"(local_min));
        if (local_min[0] < *min)
            *min = local_min[0];
#endif

        p_src += vl;
    }

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
