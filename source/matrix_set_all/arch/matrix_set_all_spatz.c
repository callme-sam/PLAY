#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int matrix_set_all_spatz_serial(float *mat, const float val, const int dim_M, const int dim_N)
{
    size_t avl;
    size_t vl;
    float *m;

    avl = dim_M * dim_N;
    m = mat;

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vfmv.v.f v0, %0" :: "f"(val));

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
        asm volatile ("vse32.v v0, (%0)" :: "r"(m));

        m += vl;
    }

    return 0;
}

int matrix_set_all_impl(float *mat, const float val, const int dim_M, const int dim_N)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = matrix_set_all_spatz_serial(mat, val, dim_M, dim_N);
#endif

    return ret;
}
