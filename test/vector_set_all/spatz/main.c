#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "snrt.h"
#include "printf.h"

float *src;
float val;

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = vector_compare(src, vec, LEN);
#ifdef  PRINT_DATA
    scalar_print(val, "value");
    vector_print(src, LEN, "result");
    vector_print(vec, LEN, "expected");
    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
#endif  /* PRINT_DATA */

    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void initialize_vectors()
{
    if (!is_master_core())
        return;

    src = my_alloc(LEN * sizeof(float));

    for (int i = 0; i < LEN; i++) {
        src[i] = 0;
    }

    val = value;
}

static void run_test()
{
    volatile int len = LEN;
    initialize_vectors();
    barrier();

    INIT_STATS();
    START_LOOP_STATS();
    START_STATS();
    vector_set_all(src, val, len);
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

static int test_vector_set_all()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'vector_set_all' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### VECTOR_SET_ALL TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_vector_set_all();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
