#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int linalg_gemv_trans(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N)
{
    return linalg_gemv_trans_impl(mat, vec_x, vec_y, alpha, beta, dst, dim_M, dim_N);
}
