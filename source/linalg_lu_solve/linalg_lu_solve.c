#include "play.h"

#include "pmsis.h"

PI_L1 float *y;

#ifdef  CLUSTER

#if 0
/* not optimized */
PI_L1 float local_sum[NUM_CORES];

static inline void barrier()
{
#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif
}

int linalg_lu_solve_parallel(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    int perm_idx;
    float sum;

    int start;
    int block;
    int left;
    int end;
    int id;

    id = pi_core_id();
    if (id == 0)
        y = pmsis_l1_malloc(dim_M * sizeof(float));

    barrier();

    /* Forward substitution (L * y = perm * v) */
    for (int m = 0; m < dim_M; m++) {
        sum = 0;
        local_sum[id] = 0;
        perm_idx = perm[m];

        block = m / NUM_CORES;
        left = m % NUM_CORES;
        start = id * block + (id < left ? id : left);
        end = start + block + (id < left ? 1 : 0);

        for (int k = start; k < end; k++)
            local_sum[id] += mat[m * dim_N + k] * y[k];

        barrier();
        if (id == 0) {
            for (int i = 0; i < NUM_CORES; i++)
                sum += local_sum[i];
            y[m] = vec[perm_idx] - sum;
        }
        barrier();
    }

    /* Backward substitution (U * x = y) */
    for (int m = (dim_M - 1); m >= 0; m--) {
        sum = 0;
        local_sum[id] = 0;

        block = (dim_N - (m + 1)) / NUM_CORES;
        left = (dim_N - (m + 1)) % NUM_CORES;
        start = id * block + (id < left ? id : left) + (m + 1);
        end = start + block + (id < left ? 1 : 0);

        for (int k = start; k < end; k++)
            local_sum[id] += mat[m * dim_N + k] * result[k];

        barrier();
        if (id == 0) {
            for (int i = 0; i < NUM_CORES; i++)
                sum += local_sum[i];
            result[m] = (y[m] - sum) / mat[m * dim_N + m];
        }
        barrier();
    }

    if (id == 0)
        pmsis_l1_malloc_free(y, dim_M * sizeof(float));

    barrier();

    return 0;
}
#endif


#if 0
/* for - unroll x2 - single acc */
PI_L1 float local_sum[NUM_CORES];

static inline void barrier()
{
#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif
}

int linalg_lu_solve_parallel(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    int perm_idx;
    float sum;

    int start;
    int block;
    int left;
    int end;
    int id;
    int k;

    id = pi_core_id();
    if (id == 0)
        y = pmsis_l1_malloc(dim_M * sizeof(float));

    barrier();

    /* Forward substitution (L * y = perm * v) */
    for (int m = 0; m < dim_M; m++) {
        sum = 0;
        local_sum[id] = 0;
        perm_idx = perm[m];

        block = m / NUM_CORES;
        left = m % NUM_CORES;
        start = id * block + (id < left ? id : left);
        end = start + block + (id < left ? 1 : 0);

        for (k = start; (k + 1) < end; k += 2) {
            float y1, y2;
            float mat1, mat2;

            y1 = y[k];
            y2 = y[k + 1];
            mat1 = mat[m * dim_N + k];
            mat2 = mat[m * dim_N + (k + 1)];

            local_sum[id] += mat1 * y1;
            local_sum[id] += mat2 * y2;
        }

        if (k != end)
            local_sum[id] += mat[m * dim_N + (end - 1)] * y[end - 1];

        barrier();
        if (id == 0) {
            for (int i = 0; i < NUM_CORES; i++)
                sum += local_sum[i];
            y[m] = vec[perm_idx] - sum;
        }
        barrier();
    }

    /* Backward substitution (U * x = y) */
    for (int m = (dim_M - 1); m >= 0; m--) {
        sum = 0;
        local_sum[id] = 0;

        block = (dim_N - (m + 1)) / NUM_CORES;
        left = (dim_N - (m + 1)) % NUM_CORES;
        start = id * block + (id < left ? id : left) + (m + 1);
        end = start + block + (id < left ? 1 : 0);

        for (k = start; (k + 1) < end; k +=2) {
            float mat1, mat2;
            float result1, result2;

            result1 = result[k];
            result2 = result[k + 1];
            mat1 = mat[m * dim_N + k];
            mat2 = mat[m * dim_N + (k + 1)];

            local_sum[id] += mat1 * result1;
            local_sum[id] += mat2 * result2;
        }

        if (k != end)
            local_sum[id] += mat[m * dim_N + (end - 1)] * result[end - 1];

        barrier();
        if (id == 0) {
            for (int i = 0; i < NUM_CORES; i++)
                sum += local_sum[i];
            result[m] = (y[m] - sum) / mat[m * dim_N + m];
        }
        barrier();
    }

    if (id == 0)
        pmsis_l1_malloc_free(y, dim_M * sizeof(float));

    barrier();

    return 0;
}
#endif


#if 0
/* for - unroll x2 - double acc */
PI_L1 float local_sum1[NUM_CORES];
PI_L1 float local_sum2[NUM_CORES];

static inline void barrier()
{
#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif
}

int linalg_lu_solve_parallel(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    int perm_idx;
    float sum;

    int start;
    int block;
    int left;
    int end;
    int id;
    int k;

    id = pi_core_id();
    if (id == 0)
        y = pmsis_l1_malloc(dim_M * sizeof(float));

    barrier();

    /* Forward substitution (L * y = perm * v) */
    for (int m = 0; m < dim_M; m++) {
        sum = 0;
        local_sum1[id] = 0;
        local_sum2[id] = 0;
        perm_idx = perm[m];

        block = m / NUM_CORES;
        left = m % NUM_CORES;
        start = id * block + (id < left ? id : left);
        end = start + block + (id < left ? 1 : 0);

        for (k = start; (k + 1) < end; k += 2) {
            float y1, y2;
            float mat1, mat2;

            y1 = y[k];
            y2 = y[k + 1];
            mat1 = mat[m * dim_N + k];
            mat2 = mat[m * dim_N + (k + 1)];

            local_sum1[id] += mat1 * y1;
            local_sum2[id] += mat2 * y2;
        }

        if (k != end)
            local_sum1[id] += mat[m * dim_N + (end - 1)] * y[end - 1];

        barrier();
        if (id == 0) {
            for (int i = 0; i < NUM_CORES; i++)
                sum += local_sum1[i] + local_sum2[i];
            y[m] = vec[perm_idx] - sum;
        }
        barrier();
    }

    /* Backward substitution (U * x = y) */
    for (int m = (dim_M - 1); m >= 0; m--) {
        sum = 0;
        local_sum1[id] = 0;
        local_sum2[id] = 0;

        block = (dim_N - (m + 1)) / NUM_CORES;
        left = (dim_N - (m + 1)) % NUM_CORES;
        start = id * block + (id < left ? id : left) + (m + 1);
        end = start + block + (id < left ? 1 : 0);

        for (k = start; (k + 1) < end; k +=2) {
            float mat1, mat2;
            float result1, result2;

            result1 = result[k];
            result2 = result[k + 1];
            mat1 = mat[m * dim_N + k];
            mat2 = mat[m * dim_N + (k + 1)];

            local_sum1[id] += mat1 * result1;
            local_sum2[id] += mat2 * result2;
        }

        if (k != end)
            local_sum1[id] += mat[m * dim_N + (end - 1)] * result[end - 1];

        barrier();
        if (id == 0) {
            for (int i = 0; i < NUM_CORES; i++)
                sum += local_sum1[i] + local_sum2[i];
            result[m] = (y[m] - sum) / mat[m * dim_N + m];
        }
        barrier();
    }

    if (id == 0)
        pmsis_l1_malloc_free(y, dim_M * sizeof(float));

    barrier();

    return 0;
}
#endif

#if 1
/* while - loop unrool x2 - single acc*/
PI_L1 float local_sum[NUM_CORES];

static inline void barrier()
{
#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif
}

int linalg_lu_solve_parallel(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    int perm_idx;
    int tot_ops;
    int rem_ops;
    float sum;
    int start;
    int block;
    int left;
    int end;
    int id;
    int op;
    int k;

    id = pi_core_id();
    if (id == 0)
        y = pmsis_l1_malloc(dim_M * sizeof(float));

    barrier();

    /* Forward substitution (L * y = perm * v) */
    for (int m = 0; m < dim_M; m++) {
        sum = 0;
        local_sum[id] = 0;
        perm_idx = perm[m];

        block = m / NUM_CORES;
        left = m % NUM_CORES;
        start = id * block + (id < left ? id : left);
        end = start + block + (id < left ? 1 : 0);
        tot_ops = (end - start) / 2;
        rem_ops = (end - start) % 2;
        k = start;
        op = 0;

        if (tot_ops != 0) {
            do {
                float y1, y2;
                float mat1, mat2;

                y1 = y[k];
                y2 = y[k + 1];
                mat1 = mat[m * dim_N + k];
                mat2 = mat[m * dim_N + (k + 1)];

                local_sum[id] += mat1 * y1;
                local_sum[id] += mat2 * y2;

                k += 2;
                op++;
            } while (op < tot_ops);
        }

        if (rem_ops)
            local_sum[id] += mat[m * dim_N + (end - 1)] * y[end - 1];

        barrier();
        if (id == 0) {
            for (int i = 0; i < NUM_CORES; i++)
                sum += local_sum[i];
            y[m] = vec[perm_idx] - sum;
        }
        barrier();
    }

    /* Backward substitution (U * x = y) */
    for (int m = (dim_M - 1); m >= 0; m--) {
        sum = 0;
        local_sum[id] = 0;

        block = (dim_N - (m + 1)) / NUM_CORES;
        left = (dim_N - (m + 1)) % NUM_CORES;
        start = id * block + (id < left ? id : left) + (m + 1);
        end = start + block + (id < left ? 1 : 0);
        tot_ops = (end - start) / 2;
        rem_ops = (end - start) % 2;
        k = start;
        op = 0;

        if (tot_ops != 0) {
            do {
                float mat1, mat2;
                float result1, result2;

                result1 = result[k];
                result2 = result[k + 1];
                mat1 = mat[m * dim_N + k];
                mat2 = mat[m * dim_N + (k + 1)];

                local_sum[id] += mat1 * result1;
                local_sum[id] += mat2 * result2;

                k += 2;
                op++;
            } while (op < tot_ops);
        }

        if (rem_ops)
            local_sum[id] += mat[m * dim_N + (end - 1)] * result[end - 1];

        barrier();
        if (id == 0) {
            for (int i = 0; i < NUM_CORES; i++)
                sum += local_sum[i];
            result[m] = (y[m] - sum) / mat[m * dim_N + m];
        }
        barrier();
    }

    if (id == 0)
        pmsis_l1_malloc_free(y, dim_M * sizeof(float));

    barrier();

    return 0;
}
#endif


#if 0
/* while - loop unrool x2 - double acc*/
PI_L1 float local_sum1[NUM_CORES];
PI_L1 float local_sum2[NUM_CORES];

static inline void barrier()
{
#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif
}

int linalg_lu_solve_parallel(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    int perm_idx;
    int tot_ops;
    int rem_ops;
    float sum;
    int start;
    int block;
    int left;
    int end;
    int id;
    int op;
    int k;

    id = pi_core_id();
    if (id == 0)
        y = pmsis_l1_malloc(dim_M * sizeof(float));

    barrier();

    /* Forward substitution (L * y = perm * v) */
    for (int m = 0; m < dim_M; m++) {
        sum = 0;
        local_sum1[id] = 0;
        local_sum2[id] = 0;
        perm_idx = perm[m];

        block = m / NUM_CORES;
        left = m % NUM_CORES;
        start = id * block + (id < left ? id : left);
        end = start + block + (id < left ? 1 : 0);
        tot_ops = (end - start) / 2;
        rem_ops = (end - start) % 2;
        k = start;
        op = 0;

        if (tot_ops != 0) {
            do {
                float y1, y2;
                float mat1, mat2;

                y1 = y[k];
                y2 = y[k + 1];
                mat1 = mat[m * dim_N + k];
                mat2 = mat[m * dim_N + (k + 1)];

                local_sum1[id] += mat1 * y1;
                local_sum2[id] += mat2 * y2;

                k += 2;
                op++;
            } while (op < tot_ops);
        }

        if (rem_ops)
            local_sum1[id] += mat[m * dim_N + (end - 1)] * y[end - 1];

        barrier();
        if (id == 0) {
            for (int i = 0; i < NUM_CORES; i++)
                sum += (local_sum1[i] + local_sum2[i]);
            y[m] = vec[perm_idx] - sum;
        }
        barrier();
    }

    /* Backward substitution (U * x = y) */
    for (int m = (dim_M - 1); m >= 0; m--) {
        sum = 0;
        local_sum1[id] = 0;
        local_sum2[id] = 0;

        block = (dim_N - (m + 1)) / NUM_CORES;
        left = (dim_N - (m + 1)) % NUM_CORES;
        start = id * block + (id < left ? id : left) + (m + 1);
        end = start + block + (id < left ? 1 : 0);
        tot_ops = (end - start) / 2;
        rem_ops = (end - start) % 2;
        k = start;
        op = 0;

        if (tot_ops != 0) {
            do {
                float mat1, mat2;
                float result1, result2;

                result1 = result[k];
                result2 = result[k + 1];
                mat1 = mat[m * dim_N + k];
                mat2 = mat[m * dim_N + (k + 1)];

                local_sum1[id] += mat1 * result1;
                local_sum2[id] += mat2 * result2;

                k += 2;
                op++;
            } while (op < tot_ops);
        }

        if (rem_ops)
            local_sum1[id] += mat[m * dim_N + (end - 1)] * result[end - 1];

        barrier();
        if (id == 0) {
            for (int i = 0; i < NUM_CORES; i++)
                sum += (local_sum1[i] + local_sum2[i]);
            result[m] = (y[m] - sum) / mat[m * dim_N + m];
        }
        barrier();
    }

    if (id == 0)
        pmsis_l1_malloc_free(y, dim_M * sizeof(float));

    barrier();

    return 0;
}
#endif

#else   /* CLUSTER */

int linalg_lu_solve_serial(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    int perm_idx;
    float sum;

    y = pmsis_l1_malloc(dim_M * sizeof(float));

    /* Forward substitution (L * y = perm * v) */
    for (int m = 0; m < dim_M; m++) {
        sum = 0;
        perm_idx = perm[m];

        for (int k = 0; k < m; k++)
            sum += mat[m * dim_N + k] * y[k];
        y[m] = vec[perm_idx] - sum;
    }

    /* Backward substitution (U * x = y) */
    for (int m = (dim_M - 1); m >= 0; m--) {
        sum = 0;

        for (int k = (m + 1); k < dim_N; k++)
            sum += mat[m * dim_N + k] * result[k];
        result[m] = (y[m] - sum) / mat[m * dim_N + m];
    }

    return 0;
}

#endif  /* CLUSTER */

__attribute__((noinline)) int linalg_lu_solve(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N)
{
    int ret;

#ifdef  CLUSTER
    ret = linalg_lu_solve_parallel(mat, vec, perm, result, dim_M, dim_N);
#else   /* CLUSTER */
    ret = linalg_lu_solve_serial(mat, vec, perm, result, dim_M, dim_N);
#endif  /* CLUSTER */

    return ret;
}
