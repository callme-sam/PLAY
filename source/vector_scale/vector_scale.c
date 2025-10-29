#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int vector_scale(const float *src, const float val, float *dst, const int len)
{
    return vector_scale_impl(src, val, dst, len);
}
