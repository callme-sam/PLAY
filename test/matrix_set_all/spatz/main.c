#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "snrt.h"
#include "printf.h"

float *src  __attribute__((aligned(32)));
float val;

static void initialize_matrices()
{
    if (!is_master_core())
        return;

    src = my_alloc(DIM_M * DIM_N * sizeof(float));

    for (int m = 0; m < DIM_M; m++) {
        for (int n = 0; n < DIM_N; n++)
            src[m * DIM_N + n] = 0;
    }

    val = value;
}

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = matrix_compare(src, mat, DIM_M, DIM_N);

#ifdef  PRINT_DATA
    scalar_print(val, "value");
    matrix_print(src, DIM_M, DIM_N, "result");
    matrix_print(mat, DIM_M, DIM_N,  "expected");
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
    matrix_set_all(src, val, m, n);
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

static int test_matrix_set_all()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'matrix_set_all' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### MATRIX_SET_ALL TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_matrix_set_all();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
