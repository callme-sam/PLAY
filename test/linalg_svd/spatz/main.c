#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "snrt.h"
#include "printf.h"

float *src __attribute__((aligned(32)));
float *mat_V __attribute__((aligned(32)));
float *vec_S  __attribute__((aligned(32)));
float *result __attribute__((allligned(32)));

static void sort_results_descending(float *result, float *mat_V, float *vec_S, const int dim_M, const int dim_N) {
    float tmp;
    int max_idx;

    if (!is_master_core())
        return;

    for (int idx = 0; idx < (dim_N - 1); idx++) {
        max_idx = idx;
        for (int n = (idx + 1); n < dim_N; n++) {
            if (fabs(vec_S[n]) > fabs(vec_S[max_idx]))
                max_idx = n;
        }

        if (max_idx != idx) {
            tmp = vec_S[max_idx];
            vec_S[max_idx] = vec_S[idx];
            vec_S[idx] = tmp;

            for (int m = 0; m < dim_M; m++) {
                tmp = result[m * dim_N + max_idx];
                result[m * dim_N + max_idx] = result[m * dim_N + idx];
                result[m * dim_N + idx] = tmp;
            }

            for (int n = 0; n < dim_N; n++) {
                tmp = mat_V[n * dim_N + max_idx];
                mat_V[n * dim_N + max_idx] = mat_V[n * dim_N + idx];
                mat_V[n * dim_N + idx] = tmp;
            }
        }
    }
}

static void initialize_data()
{
    static bool allocated = false;

    if (!is_master_core())
        return;

    if (!allocated) {
        src = my_alloc(DIM_M * DIM_N * sizeof(float));
        mat_V = my_alloc(DIM_N * DIM_N * sizeof(float));
        vec_S = my_alloc(DIM_N * sizeof(float));
        result = my_alloc(DIM_M * DIM_N * sizeof(float));
        allocated = true;
    }

    for (int m = 0; m < DIM_M; m++) {
        for (int n = 0; n < DIM_N; n++) {
            src[m * DIM_N + n] = mat[m * DIM_N + n];
            result[m * DIM_N + n] = 0;
        }
    }

    for (int m = 0; m < DIM_N; m++) {
        for (int n = 0; n < DIM_N; n++) {
            mat_V[m * DIM_N + n] = 0;
        }
    }

    for (int n = 0; n < DIM_N; n++)
        vec_S[n] = 0;
}

static void check_result()
{
    bool test_result;
    bool res_cmp;
    bool s_cmp;
    bool v_cmp;

    if (!is_master_core())
        return;

    res_cmp = matrix_compare_abs(result, expected, DIM_M, DIM_N);
    if (!res_cmp)
        printf("INFO | Result matrix is wrong\n");

    v_cmp = matrix_compare_abs(mat_V, V, DIM_N, DIM_N);
    if (!v_cmp)
        printf("INFO | V matrix is wrong\n");

    s_cmp = vector_compare_abs(vec_S, S, DIM_N);
    if (!s_cmp)
        printf("INFO | S vector is wrong\n");

    test_result = res_cmp && v_cmp && s_cmp;

#ifdef  PRINT_DATA
    matrix_print(src, DIM_M, DIM_M, "mat");
    matrix_print(mat_V, DIM_N, DIM_N, "computed V");
    matrix_print(V, DIM_N, DIM_N, "expected V");
    vector_print(vec_S, DIM_N, "computed S");
    vector_print(S, DIM_N, "expected S");
    matrix_print(result, DIM_M, DIM_N, "result");
    matrix_print(expected, DIM_M, DIM_N, "expected");
#endif  /* PRINT_DATA */

    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void run_test()
{
    volatile int m = DIM_M;
    volatile int n = DIM_N;

    INIT_STATS();
    START_LOOP_STATS();
    initialize_data();
    barrier();
    START_STATS();
    linalg_svd(src, result, mat_V, vec_S, m, n);
    STOP_STATS();
    END_LOOP_STATS();

    barrier();
    sort_results_descending(result, mat_V, vec_S, DIM_M, DIM_N);

    barrier();
    check_result();
}

static int run_test_on_spatz()
{
    run_test();
    return 0;
}

static int test_linalg_svd()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'linalg_svd' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### LINALG_SVD TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_linalg_svd();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
