#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int vector_set_all(float *vec, const float val, const int len)
{
    return vector_set_all_impl(vec, val, len);
}
