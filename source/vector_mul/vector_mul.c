#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int vector_mul(const float *src_a, const float *src_b, float *dst, const int len)
{
    return vector_mul_impl(src_a, src_b, dst, len);
}
