#include "play.h"

#include <math.h>

#include "pmsis.h"

#define MAX_ITER    (100)
#define EPSILON     (1e-12)

#ifdef  CLUSTER

PI_L1 float local_max[NUM_CORES];
PI_L1 float max_offdiag;

int matrix_set_identity(float *mat, const int dim_M)
{
    int start;
    int block;
    int left;
    int end;
    int id;

    id = pi_core_id();
    block = dim_M / NUM_CORES;
    left = dim_M % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);

    for (int m = start; m < end; m++)
            mat[m * dim_M + m] = 1.0;

    return 0;
}

int linalg_svd_jacobi_parallel(const float *src, float *dst, float *mat_V, float *vec_S, const int dim_M)
{
    int pairs_per_round;
    // float max_offdiag;
    int even_dim;
    int iter;
    int id;

    matrix_set_all(mat_V, 0, dim_M, dim_M);
    matrix_set_identity(mat_V, dim_M);
    matrix_memcpy(src, dst, dim_M, dim_M);
    pi_cl_team_barrier();

    id = pi_core_id();
    even_dim = (dim_M % 2 == 0) ? dim_M : (dim_M + 1);
    pairs_per_round = even_dim / 2;

    iter = 0;
    while (iter++ < MAX_ITER) {

        for (int round = 0; round < (even_dim - 1); round++) {
            int pair_start;
            int pair_end;
            int block;
            int left;

            block = pairs_per_round / NUM_CORES;
            left = pairs_per_round % NUM_CORES;
            pair_start = id * block + (id < left ? id : left);
            pair_end = pair_start + block + (id < left ? 1 : 0);

            local_max[id] = 0;

            for (int pair = pair_start; pair < pair_end; pair++) {
                float cos;
                float sin;
                float tau;
                float t;
                int i;
                int j;

                pi_cl_team_barrier();

                i = (round + pair) % (even_dim - 1);
                j = (pair == 0) ? (even_dim - 1) : ((even_dim - 1 - pair + round) % (even_dim - 1));

                if (i >= dim_M || j >= dim_M)
                    continue;

                if (fabs(dst[i * dim_M + j]) < EPSILON)
                    continue;

                tau = (dst[j * dim_M + j] - dst[i * dim_M + i]) / (2.0 * dst[i * dim_M + j]);
                if (tau >= 0.0)
                    t = 1.0 / (tau + sqrt(1.0 + tau * tau));
                else
                    t = 1.0 / (tau - sqrt(1.0 + tau * tau));

                cos = 1.0 / sqrt(1.0 + t * t);
                sin = t * cos;

                /* Update rows i and j of DST */
                for (int m = 0; m < dim_M; m++) {
                    float im;
                    float jm;

                    im = dst[i * dim_M + m];
                    jm = dst[j * dim_M + m];

                    dst[i * dim_M + m] = (cos * im) - (sin * jm);
                    dst[j * dim_M + m] = (sin * im) + (cos * jm);
                }

                pi_cl_team_barrier();

                /* Update cols i and j of DST */
                for (int n = 0; n < dim_M; n++) {
                    float ni;
                    float nj;

                    ni = dst[n * dim_M + i];
                    nj = dst[n * dim_M + j];

                    dst[n * dim_M + i] = (cos * ni) - (sin * nj);
                    dst[n * dim_M + j] = (sin * ni) + (cos * nj);
                }

                /* Update cols i and j of V */
                for (int n = 0; n < dim_M; n++) {
                    float ni;
                    float nj;

                    ni = mat_V[n * dim_M + i];
                    nj = mat_V[n * dim_M + j];

                    mat_V[n * dim_M + i] = (cos * ni) - (sin * nj);
                    mat_V[n * dim_M + j] = (sin * ni) + (cos * nj);
                }


                if (fabs(dst[i * dim_M + j]) > local_max[id])
                    local_max[id] = fabs(dst[i * dim_M + j]);

            } /* End of pairs for this round */

            pi_cl_team_barrier();

            /* Reduction */
            if (id == 0) {
                max_offdiag = local_max[0];
                for (int cid = 1; cid < NUM_CORES; cid++)
                    if (local_max[cid] > max_offdiag)
                        max_offdiag = local_max[cid];
            }

            pi_cl_team_barrier();

            // pi_cl_team_critical_enter();
            if (max_offdiag < EPSILON)
                break;
            // pi_cl_team_critical_exit();

        }   /* Round */

        // pi_cl_team_critical_enter();
        if (max_offdiag < EPSILON)
            break;
        // pi_cl_team_critical_exit();

    }   /* Iters */

    int block;
    int start;
    int left;
    int end;

    block = dim_M / NUM_CORES;
    left = dim_M % NUM_CORES;
    start = id * block + (id < left ? id : left);
    end = start + block + (id < left ? 1 : 0);

    for (int i = start; i < end; i++) {
        if (dst[i * dim_M + i] > 0)
            vec_S[i] = sqrt(dst[i * dim_M + i]);
        else
            vec_S[i] = 0;
    }

    return 0;
}

#else   /* CLUSTER */

int matrix_set_identity(float *mat, const int dim_M)
{
    for (int m = 0; m < dim_M; m++)
        mat[m * dim_M + m] = 1.0;

    return 0;
}

int linalg_svd_jacobi_serial(const float *src, float *dst, float *mat_V, float *vec_S, const int dim_M)
{
    int iter;
    float max_offdiag;

    matrix_set_all(mat_V, 0, dim_M, dim_M);
    matrix_set_identity(mat_V, dim_M);
    matrix_memcpy(src, dst, dim_M, dim_M);

    iter = 0;
    while (iter++ < MAX_ITER) {
        max_offdiag = 0;

        for (int i = 0; i < (dim_M - 1); i++) {
            for (int j = (i + 1); j < dim_M; j++) {
                float cos;
                float sin;
                float tau;
                float t;

                if (fabs(dst[i * dim_M + j]) < EPSILON)
                    continue;

                tau = (dst[j * dim_M + j] - dst[i * dim_M + i]) / (2.0 * dst[i * dim_M + j]);
                if (tau >= 0.0)
                    t = 1.0 / (tau + sqrt(1.0 + tau * tau));
                else
                    t = 1.0 / (tau - sqrt(1.0 + tau * tau));

                cos = 1.0 / sqrt(1.0 + t * t);
                sin = t * cos;

                /* Update rows i and j of DST */
                for (int m = 0; m < dim_M; m++) {
                    float im;
                    float jm;

                    im = dst[i * dim_M + m];
                    jm = dst[j * dim_M + m];

                    dst[i * dim_M + m] = (cos * im) - (sin * jm);
                    dst[j * dim_M + m] = (sin * im) + (cos * jm);
                }

                /* Update cols i and j of DST */
                for (int n = 0; n < dim_M; n++) {
                    float ni;
                    float nj;

                    ni = dst[n * dim_M + i];
                    nj = dst[n * dim_M + j];

                    dst[n * dim_M + i] = (cos * ni) - (sin * nj);
                    dst[n * dim_M + j] = (sin * ni) + (cos * nj);
                }

                /* Update cols i and j of V */
                for (int n = 0; n < dim_M; n++) {
                    float ni;
                    float nj;

                    ni = mat_V[n * dim_M + i];
                    nj = mat_V[n * dim_M + j];

                    mat_V[n * dim_M + i] = (cos * ni) - (sin * nj);
                    mat_V[n * dim_M + j] = (sin * ni) + (cos * nj);
                }

                if (fabs(dst[i * dim_M + j]) > max_offdiag)
                    max_offdiag = fabs(dst[i * dim_M + j]);
            }
        }

        if (max_offdiag < EPSILON)
            break;
    }

    /* Extract singular values as sqrt of diag(DST) */
    for (int i = 0; i < dim_M; i++) {
        if (dst[i * dim_M + i] > 0.0)
            vec_S[i] = sqrt(dst[i * dim_M + i]);
        else
            vec_S[i] = 0.0;
    }

    return 0;
}

#endif  /* CLUSTER */


int linalg_svd_jacobi(const float *src, float *dst, float *mat_V, float *vec_S, const int dim_M)
{
    int ret;

#ifdef  CLUSTER
    ret = linalg_svd_jacobi_parallel(src, dst, mat_V, vec_S, dim_M);
#else   /* CLUSTER */
    ret = linalg_svd_jacobi_serial(src, dst, mat_V, vec_S, dim_M);
#endif  /* CLUSTER */

    return ret;
}
