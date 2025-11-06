#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int matrix_trans(const float *src, float *dst, const int dim_M, const int dim_N)
{
    return matrix_trans_impl(src, dst, dim_M, dim_N);
}
