#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int linalg_svd(const float *src, float *dst, float *mat_V, float *vec_S, const int dim_M, const int dim_N)
{
    return linalg_svd_impl(src, dst, mat_V, vec_S, dim_M, dim_N);
}
