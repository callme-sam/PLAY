#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "snrt.h"
#include "printf.h"

float *mat __attribute__((aligned(32)));
float *vec __attribute__((aligned(32)));
int *perm  __attribute__((aligned(32)));
float *result __attribute__((aligned(32)));

static void initialize_data()
{
    if (!is_master_core())
        return;

    mat = my_alloc(DIM_M * DIM_M * sizeof(float));
    vec = my_alloc(DIM_M * sizeof(float));
    perm = my_alloc(DIM_M * sizeof(int));
    result = my_alloc(DIM_M * sizeof(float));

    for (int m = 0; m < DIM_M; m++){
        for (int n = 0; n < DIM_M; n++)
            mat[m * DIM_M + n] = LU[m * DIM_M + n];
    }

    for (int m = 0; m < DIM_M; m++) {
        vec[m] = b[m];
        perm[m] = p[m];
        result[m] = 0;
    }
}

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = vector_compare(result, expected, DIM_M);

#ifdef  PRINT_DATA
    matrix_print(mat, DIM_M, DIM_M, "mat");
    vector_print((float *)perm, DIM_M, "perm");
    vector_print(vec, DIM_M, "vec");
    vector_print(expected, DIM_M, "expected");
    vector_print(result, DIM_M, "result");
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
    linalg_lu_solve(mat, vec, perm, result, m, m);
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

static int test_linalg_lu_solve()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'linalg_lu_solve' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### LINALG_LU_SOLVE TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_linalg_lu_solve();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
