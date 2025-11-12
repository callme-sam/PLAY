#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "snrt.h"
#include "printf.h"

int *perm  __attribute__((aligned(32)));
float *src __attribute__((aligned(32)));

static void initialize_data()
{
    if (!is_master_core())
        return;

    perm = my_alloc(DIM_M * sizeof(float));
    src = my_alloc(DIM_M * DIM_N * sizeof(float));

    for (int m = 0; m < DIM_M; m++){
        for (int n = 0; n < DIM_N; n++)
            src[m * DIM_N + n] = mat[m * DIM_N + n];
    }

    for (int m = 0; m < DIM_M; m++) {
        perm[m] = 0;
    }
}

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = matrix_compare(src, expected_mat, DIM_M, DIM_N);
    if (test_result)
        test_result = vector_compare((float *) perm, (float *) expected_perm, DIM_M);

#ifdef  PRINT_DATA
    matrix_print(src, DIM_M, DIM_N, "result");
    matrix_print(expected_mat, DIM_M, DIM_N, "expected mat");
    vector_print((float *)perm, DIM_M, "computed permutation");
    vector_print((float *)expected_perm, DIM_M, "expected permutation");
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
    linalg_lu_decomp(src, perm, m, n);
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

static int test_linalg_lu_decomp()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'linalg_lu_decomp' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### LINALG_LU_DECOMP TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_linalg_lu_decomp();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
