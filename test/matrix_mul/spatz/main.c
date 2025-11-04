#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "snrt.h"
#include "printf.h"

float *src_a  __attribute__((aligned(32)));
float *src_b __attribute__((aligned(32)));
float *result __attribute__((aligned(32)));

static void initialize_matrices()
{
    if (!is_master_core())
        return;

    src_a = my_alloc(DIM_M * DIM_N * sizeof(float));
    src_b = my_alloc(DIM_N * DIM_P * sizeof(float));
    result = my_alloc(DIM_M * DIM_P * sizeof(float));

    for (int m = 0; m < DIM_M; m++) {
        for (int n = 0; n < DIM_N; n++)
            src_a[m * DIM_N + n] = mat_a[m * DIM_N + n];
    }

    for (int n = 0; n < DIM_N; n++) {
        for (int p = 0; p < DIM_P; p++)
            src_b[n * DIM_P + p] = mat_b[n * DIM_P + p];
    }

    for (int m = 0; m < DIM_M; m++) {
        for (int p = 0; p < DIM_P; p++) {
            result[m * DIM_P + p] = 0;
        }
    }
}

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = matrix_compare(result, expected, DIM_M, DIM_P);

#ifdef  PRINT_DATA
    matrix_print(src_a, DIM_M, DIM_N, "src_a");
    matrix_print(src_b, DIM_N, DIM_P, "src_b");
    matrix_print(result, DIM_M, DIM_P, "result");
    matrix_print(expected, DIM_M, DIM_P, "expected");
#endif  /* PRINT_DATA */

    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void run_test()
{
    volatile int m = DIM_M;
    volatile int n = DIM_N;
    volatile int p = DIM_P;
    initialize_matrices();
    barrier();

    INIT_STATS();
    START_LOOP_STATS();
    START_STATS();
    matrix_mul(src_a, src_b, result, m, n, p);
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

static int test_matrix_mul()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'matrix_mul' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### MATRIX_MUL TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_matrix_mul();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
