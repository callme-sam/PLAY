#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int vector_axpy(const float *src_a, const float *src_b, const float alpha, float *dst, const int len)
{
    return vector_axpy_impl(src_a, src_b, alpha, dst, len);
}
