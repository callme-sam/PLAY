#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "snrt.h"
#include "printf.h"

float beta;
float alpha;
float *mat;
float *vec_x;
float *vec_y;
float *result;

static void initialize_data()
{
    if (!is_master_core())
        return;

    mat = my_alloc(DIM_M * DIM_N * sizeof(float));
    vec_x = my_alloc(DIM_N * sizeof(float));
    vec_y = my_alloc(DIM_M * sizeof(float));
    result = my_alloc(DIM_M * sizeof(float));

    for (int m = 0; m < DIM_M; m++)
        for (int n = 0; n < DIM_N; n++)
            mat[m * DIM_N + n] = matA[m * DIM_N + n];

    for (int m = 0; m < DIM_M; m++) {
        vec_y[m] = vecY[m];
        result[m] = 0;
    }

    for (int n = 0; n < DIM_N; n++)
        vec_x[n] = vecX[n];

    alpha = a;
    beta = b;
}

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = vector_compare(result, expected, DIM_M);

#ifdef  PRINT_DATA
    scalar_print(alpha, "alpha");
    scalar_print(beta, "beta");
    vector_print(vec_x, DIM_N, "vec_x");
    vector_print(vec_y, DIM_M, "vec_y");
    matrix_print(mat, DIM_M, DIM_N, "mat");
    vector_print(result, DIM_M, "result");
    vector_print(expected, DIM_M, "expected");
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
    linalg_gemv(mat, vec_x, vec_y, alpha, beta, result, m, n);
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

static int test_linalg_gemv()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'linalg_gemv' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### LINALG_GEMV TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_linalg_gemv();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
