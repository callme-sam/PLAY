#include "internal/arch_interface.h"
#include "play.h"

__attribute__((noinline)) int matrix_swap_rows(float *mat, const int row_a, const int row_b, const int dim_M, const int dim_N)
{
    return matrix_swap_rows_impl(mat, row_a, row_b, dim_M, dim_N);
}
