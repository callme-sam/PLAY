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

static void sort_results_descending(float *result, float *mat_V, float *vec_S, const int dim_M) {
    float tmp;
    int max_idx;

    if (!is_master_core())
        return;

    for (int i = 0; i < (dim_M - 1); i++) {
        max_idx = i;
        for (int j = (i + 1); j < dim_M; j++) {
            if (fabs(vec_S[j]) > fabs(vec_S[max_idx])) {
                max_idx = j;
            }
        }

        if (max_idx != i) {
            tmp = vec_S[i];
            vec_S[i] = vec_S[max_idx];
            vec_S[max_idx] = tmp;

            tmp = result[i * dim_M + i];
            result[i * dim_M + i] = result[max_idx * dim_M + max_idx];
            result[max_idx * dim_M + max_idx] = tmp;

            for (int k = 0; k < dim_M; k++) {
                tmp = mat_V[k * dim_M + i];
                mat_V[k * dim_M + i] = mat_V[k * dim_M + max_idx];
                mat_V[k * dim_M + max_idx] = tmp;
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
        src = my_alloc(DIM_M * DIM_M * sizeof(float));
        mat_V = my_alloc(DIM_M * DIM_M * sizeof(float));
        vec_S = my_alloc(DIM_M * sizeof(float));
        allocated = true;
    }

    for (int m = 0; m < DIM_M; m++) {
        for (int n = 0; n < DIM_M; n++) {
            src[m * DIM_M + n] = mat[m * DIM_M + n];
            mat_V[m * DIM_M + n] = 0;
        }
    }

    for (int m = 0; m < DIM_M; m++)
        vec_S[m] = 0;
}

static void check_result()
{
    bool test_result;
    bool res_cmp;
    bool s_cmp;
    bool v_cmp;

    if (!is_master_core())
        return;

    res_cmp = matrix_compare_abs(src, expected, DIM_M, DIM_M);
    if (!res_cmp)
        printf("INFO | Result matrix is wrong\n");

    v_cmp = matrix_compare_abs(mat_V, V, DIM_M, DIM_M);
    if (!v_cmp)
        printf("INFO | V matrix is wrong\n");

    s_cmp = vector_compare_abs(vec_S, S, DIM_M);
    if (!s_cmp)
        printf("INFO | S vector is wrong\n");

    test_result = res_cmp && v_cmp && s_cmp;

#ifdef  PRINT_DATA
    matrix_print(mat_V, DIM_M, DIM_M, "computed V");
    matrix_print(V, DIM_M, DIM_M, "expected V");
    vector_print(vec_S, DIM_M, "computed S");
    vector_print(S, DIM_M, "expected S");
    matrix_print(src, DIM_M, DIM_M, "result");
    matrix_print(expected, DIM_M, DIM_M, "expected");
#endif  /* PRINT_DATA */

    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void run_test()
{
    volatile int m = DIM_M;

    INIT_STATS();
    START_LOOP_STATS();
    initialize_data();
    barrier();
    START_STATS();
    linalg_svd_jacobi(src, mat_V, vec_S, m);
    STOP_STATS();
    END_LOOP_STATS();

    barrier();
    sort_results_descending(src, mat_V, vec_S, DIM_M);

    barrier();
    check_result();
}

static int run_test_on_spatz()
{
    run_test();
    return 0;
}

static int test_linalg_svd_jacobi()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'linalg_svd_jacobi' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### LINALG_SVD_JACOBI TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_linalg_svd_jacobi();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
