#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int matrix_swap_rows_spatz_serial(float *mat, const int row_a, const int row_b, const int dim_N)
{
    size_t avl;
    size_t vl;

    float *mat_row_a;
    float *mat_row_b;

    mat_row_a = mat + (row_a * dim_N);
    mat_row_b = mat + (row_b * dim_N);
    avl = dim_N;

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vle32.v v0, (%0)" :: "r"(mat_row_a));
        asm volatile ("vle32.v v8, (%0)" :: "r"(mat_row_b));

        asm volatile ("vse32.v v0, (%0)" :: "r"(mat_row_b));
        asm volatile ("vse32.v v8, (%0)" :: "r"(mat_row_a));

        mat_row_a += vl;
        mat_row_b += vl;
    }

    return 0;
}

int matrix_swap_rows_impl(float *mat, const int row_a, const int row_b, const int dim_N)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = matrix_swap_rows_spatz_serial(mat, row_a, row_b, dim_N);
#endif

    return ret;
}
