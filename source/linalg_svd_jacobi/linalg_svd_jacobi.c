#include "play.h"

#include <math.h>

#include "pmsis.h"

static PI_L1 float ONE_f = 1;
static PI_L1 float TWO_f = 2;
static PI_L1 int MAX_ITER = 100;
static PI_L1 float EPSILON = 1e-12;

#ifdef  CLUSTER

PI_L1 float local_max[NUM_CORES];
PI_L1 float max_offdiag;

static inline void barrier()
{
#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif
}

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

    barrier();

    return 0;
}

int linalg_svd_jacobi_parallel( float *mat, float *mat_V, float *vec_S, const int dim_M)
{
    int pairs_per_round;
    int even_dim;
    int iter;
    int id;

    matrix_set_identity(mat_V, dim_M);

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

                barrier();

                i = (round + pair) % (even_dim - 1);
                j = (pair == 0) ? (even_dim - 1) : ((even_dim - 1 - pair + round) % (even_dim - 1));

                if (i >= dim_M || j >= dim_M)
                    continue;

                if (fabs(mat[i * dim_M + j]) < EPSILON)
                    continue;

                tau = (mat[j * dim_M + j] - mat[i * dim_M + i]) / (TWO_f * mat[i * dim_M + j]);
                if (tau >= 0.0)
                    t = ONE_f / (tau + sqrtf(ONE_f + tau * tau));
                else
                    t = ONE_f / (tau - sqrtf(ONE_f + tau * tau));

                cos = ONE_f / sqrtf(ONE_f + t * t);
                sin = t * cos;

                /* Update rows i and j of MAT */
                for (int m = 0; m < dim_M; m++) {
                    float im;
                    float jm;

                    im = mat[i * dim_M + m];
                    jm = mat[j * dim_M + m];

                    mat[i * dim_M + m] = (cos * im) - (sin * jm);
                    mat[j * dim_M + m] = (sin * im) + (cos * jm);
                }

                barrier();

                /* Update cols i and j of MAT */
                for (int n = 0; n < dim_M; n++) {
                    float ni;
                    float nj;

                    ni = mat[n * dim_M + i];
                    nj = mat[n * dim_M + j];

                    mat[n * dim_M + i] = (cos * ni) - (sin * nj);
                    mat[n * dim_M + j] = (sin * ni) + (cos * nj);
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


                if (fabs(mat[i * dim_M + j]) > local_max[id])
                    local_max[id] = fabs(mat[i * dim_M + j]);

            } /* End of pairs for this round */

            barrier();

            /* Reduction */
            if (id == 0) {
                max_offdiag = local_max[0];
                for (int cid = 1; cid < NUM_CORES; cid++)
                    if (local_max[cid] > max_offdiag)
                        max_offdiag = local_max[cid];
            }

            barrier();

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
        if (mat[i * dim_M + i] > 0)
            vec_S[i] = sqrtf(mat[i * dim_M + i]);
        else
            vec_S[i] = 0;
    }

    barrier();

    return 0;
}

#else   /* CLUSTER */

int matrix_set_identity(float *mat, const int dim_M)
{
    for (int m = 0; m < dim_M; m++)
        mat[m * dim_M + m] = 1.0;

    return 0;
}

int linalg_svd_jacobi_serial(float *mat, float *mat_V, float *vec_S, const int dim_M)
{
    int iter;
    float max_offdiag;

    matrix_set_identity(mat_V, dim_M);

    iter = 0;
    while (iter++ < MAX_ITER) {
        max_offdiag = 0;

        for (int i = 0; i < (dim_M - 1); i++) {
            for (int j = (i + 1); j < dim_M; j++) {
                float cos;
                float sin;
                float tau;
                float t;

                if (fabs(mat[i * dim_M + j]) < EPSILON)
                    continue;

                tau = (mat[j * dim_M + j] - mat[i * dim_M + i]) / (2.0 * mat[i * dim_M + j]);
                if (tau >= 0.0)
                    t = 1.0 / (tau + sqrtf(1.0 + tau * tau));
                else
                    t = 1.0 / (tau - sqrtf(1.0 + tau * tau));

                cos = 1.0 / sqrtf(1.0 + t * t);
                sin = t * cos;

                /* Update rows i and j of MAT */
                for (int m = 0; m < dim_M; m++) {
                    float im;
                    float jm;

                    im = mat[i * dim_M + m];
                    jm = mat[j * dim_M + m];

                    mat[i * dim_M + m] = (cos * im) - (sin * jm);
                    mat[j * dim_M + m] = (sin * im) + (cos * jm);
                }

                /* Update cols i and j of MAT */
                for (int n = 0; n < dim_M; n++) {
                    float ni;
                    float nj;

                    ni = mat[n * dim_M + i];
                    nj = mat[n * dim_M + j];

                    mat[n * dim_M + i] = (cos * ni) - (sin * nj);
                    mat[n * dim_M + j] = (sin * ni) + (cos * nj);
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

                if (fabs(mat[i * dim_M + j]) > max_offdiag)
                    max_offdiag = fabs(mat[i * dim_M + j]);
            }
        }

        if (max_offdiag < EPSILON)
            break;
    }

    /* Extract singular values as sqrtf of diag(MAT) */
    for (int i = 0; i < dim_M; i++) {
        if (mat[i * dim_M + i] > 0.0)
            vec_S[i] = sqrtf(mat[i * dim_M + i]);
        else
            vec_S[i] = 0.0;
    }

    return 0;
}

#endif  /* CLUSTER */


__attribute__((noinline)) int linalg_svd_jacobi(float *mat, float *mat_V, float *vec_S, const int dim_M)
{
    int ret;

#ifdef  CLUSTER
    ret = linalg_svd_jacobi_parallel(mat, mat_V, vec_S, dim_M);
#else   /* CLUSTER */
    ret = linalg_svd_jacobi_serial(mat, mat_V, vec_S, dim_M);
#endif  /* CLUSTER */

    return ret;
}
