#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "snrt.h"
#include "printf.h"

float *src;
float result;

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = scalar_compare(result, expected);

#ifdef  PRINT_DATA
    vector_print(src, LEN, "src");
    scalar_print(result, "result");
    scalar_print(expected, "expected");
#endif  /* PRINT_DATA */

    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void initialize_vectors()
{
    if (!is_master_core())
        return;

    src = my_alloc(LEN * sizeof(float));

    result = 0;
    for (int i = 0; i < LEN; i++) {
        src[i] = vec[i];
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
    vector_min(src, &result, len);
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

static int test_vector_min()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("INFO | Running 'vector_min' test on Spatz Cluster\n");
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### VECTOR_MIN TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_vector_min();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

int main()
{
    return test_kickoff();
}
