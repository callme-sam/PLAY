#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "snrt.h"
#include "printf.h"

float *src __attribute__((aligned(32)));
float *result __attribute__((aligned(32)));

static void initialize_data()
{
    static bool allocated = false;

    if (!is_master_core())
        return;

    if (!allocated) {
        src = my_alloc(DIM_M * DIM_M * sizeof(float));
        result = my_alloc(DIM_M * DIM_M * sizeof(float));
        allocated = true;
    }

    for (int m = 0; m < DIM_M; m++) {
        for (int n = 0; n < DIM_M; n++) {
            src[m * DIM_M + n] = mat[m * DIM_M + n];
            result[m * DIM_M + n] = 0;
        }
    }
}

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = matrix_compare(result, expected, DIM_M, DIM_M);

#ifdef  PRINT_DATA
    matrix_print(src, DIM_M, DIM_M, "mat");
    matrix_print(result, DIM_M, DIM_M, "result");
    matrix_print(expected, DIM_M, DIM_M, "expected");
#endif  /* PRINT_DATA */

    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void run_test()
{
    volatile int m = DIM_M;
    initialize_data();
    barrier();

    INIT_STATS();
    START_LOOP_STATS();
    START_STATS();
    linalg_cholesky_decomp(src, result, m);
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

static int test_linalg_cholesky_decomp()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'linalg_cholesky_decomp' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### LINALG_CHOLESKY_DECOMP TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_linalg_cholesky_decomp();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
