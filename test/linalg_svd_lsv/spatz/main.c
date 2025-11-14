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
float *result __attribute__((aligned(32)));

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
            mat_V[m * DIM_N + n] = V[m * DIM_N + n];
        }
    }

    for (int n = 0; n < DIM_N; n++)
        vec_S[n] = S[n];
}

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = matrix_compare_abs(result, expected, DIM_M, DIM_N);

#ifdef PRINT_DATA
    matrix_print(src, DIM_M, DIM_N, "mat");
    matrix_print(mat_V, DIM_N, DIM_N, "V");
    vector_print(vec_S, DIM_N, "S");
    matrix_print(result, DIM_M, DIM_N, "result");
    matrix_print(expected, DIM_M, DIM_N, "expected");
#endif  /* PRINT_DATA */

    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void run_test()
{
    volatile int m = DIM_M;
    volatile int n = DIM_N;
    initialize_data();
    barrier();

    INIT_STATS();
    START_LOOP_STATS();
    START_STATS();
    linalg_svd_lsv(src, mat_V, vec_S, result, m, n);
    STOP_STATS();
    END_LOOP_STATS();

    barrier();
    check_result();
}

static int run_test_on_spatz()
{
    run_test();
    return 0;
}

static int test_linalg_svd_lsv()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'linalg_svd_lsv' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### LINALG_SVD_LSV TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_linalg_svd_lsv();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
