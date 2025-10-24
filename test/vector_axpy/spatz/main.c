#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "snrt.h"
#include "printf.h"

float *src_a;
float *src_b;
float *result;
float alpha_val;

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = vector_compare(result, expected, LEN);
#ifdef  PRINT_DATA
    vector_print(src_a, LEN, "src_a");
    vector_print(src_b, LEN, "src_b");
    scalar_print(alpha_val, "alpha");
    vector_print(result, LEN, "result");
    vector_print(expected, LEN, "expected");
#endif  /* PRINT_DATA */

    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void initialize_vectors()
{
    if (!is_master_core())
        return;

    src_a = my_alloc(LEN * sizeof(float));
    src_b = my_alloc(LEN * sizeof(float));
    result = my_alloc(LEN * sizeof(float));

    alpha_val = scalar;
    for (int i = 0; i < LEN; i++) {
        src_a[i] = vec_a[i];
        src_b[i] = vec_b[i];
        result[i] = 0;
    }
}

static void run_test()
{
    volatile int len = LEN;
    initialize_vectors();
    barrier();

    INIT_STATS();
    START_LOOP_STATS();
    START_STATS();
    vector_axpy(src_a, src_b, alpha_val, result, len);
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

static int test_vector_axpy()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'vector_axpy' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### VECTOR_AXPY TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_vector_axpy();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
