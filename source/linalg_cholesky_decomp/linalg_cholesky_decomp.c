#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int linalg_cholesky_decomp(const float *src, float *dst, const int dim)
{
    return linalg_cholesky_decomp_impl(src, dst, dim);
}
