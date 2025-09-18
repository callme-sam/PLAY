#include "play.h"

#include "pmsis.h"

PI_L1 float *tmp;

#ifdef  CLUSTER

int linalg_svd_parallel(const float *src, float *dst, float *mat_V, float *vec_S, const int dim_M, const int dim_N)
{
    if (pi_core_id() == 0)
        tmp = pmsis_l1_malloc(dim_N * dim_N * sizeof(float));

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    matrix_mul_trans_A(src, src, tmp, dim_M, dim_N, dim_N);
    linalg_svd_jacobi(tmp, tmp, mat_V, vec_S, dim_N);
    linalg_svd_lsv(src, mat_V, vec_S, dst, dim_M, dim_N);

    if (pi_core_id() == 0)
        pmsis_l1_malloc_free(tmp, dim_N * dim_N * sizeof(float));

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}

#else   /* CLUSTER */


int linalg_svd_serial(const float *src, float *dst, float *mat_V, float *vec_S, const int dim_M, const int dim_N)
{
    tmp = pmsis_l1_malloc(dim_N * dim_N * sizeof(float));
    matrix_mul_trans_A(src, src, tmp, dim_M, dim_N, dim_N);
    linalg_svd_jacobi(tmp, tmp, mat_V, vec_S, dim_N);
    linalg_svd_lsv(src, mat_V, vec_S, dst, dim_M, dim_N);
    pmsis_l1_malloc_free(tmp, dim_N * dim_N * sizeof(float));
    return 0;
}

#endif  /* CLUSTER */

__attribute__((noinline)) int linalg_svd(const float *src, float *dst, float *mat_V, float *vec_S, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = linalg_svd_parallel(src, dst, mat_V, vec_S, dim_M, dim_N);
#else   /* CLUSTER */
    ret = linalg_svd_serial(src, dst, mat_V, vec_S, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
