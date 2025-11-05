#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int matrix_mul_trans_A(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    return matrix_mul_trans_A_impl(src_a, src_b, dst, dim_M, dim_N, dim_P);
}
