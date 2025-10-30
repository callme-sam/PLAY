#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int vector_memcpy(const float *src, float *dst, const int len)
{
    return vector_memcpy_impl(src, dst, len);
}
