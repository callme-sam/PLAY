#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int linalg_svd_spatz_serial(const float *src, float *dst, float *mat_V, float *vec_S, const int dim_M, const int dim_N)
{
    float *tmp;

    tmp = snrt_l1alloc(dim_N * dim_N * sizeof(float));

    matrix_mul_trans_A(src, src, tmp, dim_M, dim_N, dim_N);
    linalg_svd_jacobi(tmp, mat_V, vec_S, dim_N);
    linalg_svd_lsv(src, mat_V, vec_S, dst, dim_M, dim_N);

#if 0
    /* snrt does not provide a free api */
    snrt_l1free(tmp, dim_N * dim_N * sizeof(float));
#endif

    return 0;
}

int linalg_svd_impl(const float *src, float *dst, float *mat_V, float *vec_S, const int dim_M, const int dim_N)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = linalg_svd_spatz_serial(src, dst, mat_V, vec_S, dim_M, dim_N);
#endif

    return ret;
}
