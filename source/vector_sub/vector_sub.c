#include "arch/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int vector_sub(const float *src_a, const float *src_b, float *dst, const int len)
{
    int ret;

#if TARGET_IS_PULP_OPEN
    ret = vector_sub_pulp_open(src_a, src_b, dst, len);
#elif TARGET_IS_SPATZ
    ret = vector_sub_spatz(src_a, src_b, dst, len);
#endif /* TARGET_IS_ */

    return ret;
}
