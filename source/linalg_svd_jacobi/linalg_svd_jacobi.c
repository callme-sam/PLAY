#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int linalg_svd_jacobi(float *mat, float *mat_V, float *vec_S, const int dim_M)
{
    return linalg_svd_jacobi_impl(mat, mat_V, vec_S, dim_M);
}
