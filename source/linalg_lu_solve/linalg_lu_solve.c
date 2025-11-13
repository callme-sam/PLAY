#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int linalg_lu_solve(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    return linalg_lu_solve_impl(mat, vec, perm, result, dim_M, dim_N);
}
