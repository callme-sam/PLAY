#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int vector_offset(const float *src, const float offset, float *dst, const int len)
{
    return vector_offset_impl(src, offset, dst, len);
}
