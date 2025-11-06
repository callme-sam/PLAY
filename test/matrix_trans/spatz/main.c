#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "snrt.h"
#include "printf.h"

float *src;
float *result;

static void initialize_matrices()
{
    if (!is_master_core())
        return;

    src = my_alloc(DIM_M * DIM_N * sizeof(float));
    result = my_alloc(DIM_M * DIM_N * sizeof(float));

    for (int m = 0; m < DIM_M; m++) {
        for (int n = 0; n < DIM_N; n++)
            src[m * DIM_N + n] = mat[m * DIM_N + n];
    }

    for (int m = 0; m < DIM_M; m++) {
        for (int n = 0; n < DIM_N; n++) {
            result[m * DIM_N + n] = 0;
        }
    }
}

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = matrix_compare(result, expected, DIM_N, DIM_M);

#ifdef  PRINT_DATA
    matrix_print(src, DIM_M, DIM_N, "src");
    matrix_print(result, DIM_N, DIM_M, "result");
    matrix_print(expected, DIM_N, DIM_M, "expected");
#endif  /* PRINT_DATA */

    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void run_test()
{
    volatile int m = DIM_M;
    volatile int n = DIM_N;
    initialize_matrices();
    barrier();

    INIT_STATS();
    START_LOOP_STATS();
    START_STATS();
    matrix_trans(src, result, m, n);
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

static int test_matrix_trans()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'matrix_trans' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### MATRIX_TRANS TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_matrix_trans();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
