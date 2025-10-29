#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"


static int vector_set_all_spatz_serial(float *vec, const float val, const int len)
{
    const float *v;
    size_t avl;
    size_t vl;

    avl = len;
    v = vec;

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vfmv.v.f v0, %0" :: "f"(val));

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
        asm volatile ("vse32.v v0, (%0)" :: "r"(v));

        v += vl;
    }

    return 0;
}

int vector_set_all_impl(float *vec, const float val, const int len)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = vector_set_all_spatz_serial(vec, val, len);
#endif

    return ret;
}
