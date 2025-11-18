#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "snrt.h"
#include "printf.h"

int row_a;
int row_b;
float *src __attribute__((aligned(32)));
float *result __attribute__((aligned(32)));

static void initialize_matrices()
{
    if (!is_master_core())
        return;

    src = my_alloc(DIM_M * DIM_N * sizeof(float));
    result = my_alloc(DIM_M * DIM_N * sizeof(float));

    for (int m = 0; m < DIM_M; m++) {
        for (int n = 0; n < DIM_N; n++) {
            src[m * DIM_N + n] = mat[m * DIM_N + n];
            result[m * DIM_N + n] = mat[m * DIM_N + n];
        }
    }

    row_a = rowA;
    row_b = rowB;
}

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = matrix_compare(result, expected, DIM_M, DIM_N);

#ifdef  PRINT_DATA
    scalar_print(row_a, "row_a");
    scalar_print(row_b, "row_b");
    matrix_print(src, DIM_M, DIM_N, "src");
    matrix_print(result, DIM_M, DIM_N, "result");
    matrix_print(expected, DIM_M, DIM_N,  "expected");
#endif  /* PRINT_DATA */

    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void run_test()
{
    volatile int n = DIM_N;

    INIT_STATS();
    START_LOOP_STATS();
    initialize_matrices();
    barrier();
    START_STATS();
    matrix_swap_rows(result, row_a, row_b, n);
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

static int test_matrix_swap_rows()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'matrix_swap_rows' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### MATRIX_SWAP_ROWS TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_matrix_swap_rows();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
