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

static void initialize_vectors()
{
    if (!is_master_core())
        return;

    src_a = my_alloc(LEN * sizeof(float));
    src_b = my_alloc(LEN * sizeof(float));
    result = my_alloc(sizeof(float));

    *result = 0;
    for (int i = 0; i < LEN; i++) {
        src_a[i] = vec_a[i];
        src_b[i] = vec_b[i];
    }
}

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = scalar_compare(*result, expected);

#ifdef  PRINT_DATA
    vector_print(src_a, LEN, "src_a");
    vector_print(src_b, LEN, "src_b");
    scalar_print(*result, "result");
    scalar_print(expected, "expected");
#endif  /* PRINT_DATA */

    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void run_test()
{
    volatile int len = LEN;
    initialize_vectors();
    barrier();

    INIT_STATS();
    START_LOOP_STATS();
    START_STATS();
    vector_dot(src_a, src_b, result, len);
    STOP_STATS();
    END_LOOP_STATS();

    barrier();
    check_result();
}

static int test_vector_dot()
{
    int ret;

    if (is_master_core()) printf("INFO | Running 'vector_dot' test on Spatz Cluster\n");

    ret = 0;
    run_test();

    if (is_master_core()) {
#ifdef  ENABLE_LOGGING
        if (ret)
            printf("ERROR | Unable to run test on cluster\n");
#endif  /* ENABLE_LOGGING */
    }

    return ret;
}

static int test_kickoff()
{
    int ret;

    if (is_master_core()) printf("\n##################################### VECTOR_DOT TEST ####################################\n\n");

    ret = test_vector_dot();

    if (is_master_core()) printf("\n##########################################################################################\n\n");

    return ret;
}

int main()
{
    return test_kickoff();
}
