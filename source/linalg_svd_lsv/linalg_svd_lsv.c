#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int linalg_svd_lsv(const float *src, float *mat_V, float *vec_S, float *dst, const int dim_M, const int dim_N)
{
    return linalg_svd_lsv_impl(src, mat_V, vec_S, dst, dim_M, dim_N);
}
