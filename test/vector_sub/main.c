#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#ifdef  SPATZ
#include "snrt.h"
#include "printf.h"
#define PI_L1   /* mock */
#else   /* SPATZ */
#include "pmsis.h"
#endif

PI_L1 float *src_a;
PI_L1 float *src_b;
PI_L1 float *result;

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = vector_compare(result, expected, LEN);
#ifdef  PRINT_DATA
    vector_print(src_a, LEN, "src_a");
    vector_print(src_b, LEN, "src_b");
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

    for (int i = 0; i < LEN; i++) {
        src_a[i] = vec_a[i];
        src_b[i] = vec_b[i];
        result[i] = 0;
    }
}

#ifdef  SPATZ

int main()
{
#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##################################### VECTOR_SUB TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    volatile int len = LEN;
    initialize_vectors();
    barrier();

    INIT_STATS();
    START_LOOP_STATS();
    START_STATS();
    vector_sub(src_a, src_b, result, len);
    STOP_STATS();
    END_LOOP_STATS();

    barrier();
    check_result();

#ifdef  ENABLE_LOGGING
    if (is_master_core()) printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */
}

#else   /* SPATZ */

static void run_test()
{
    volatile int len = LEN;
    initialize_vectors();
    barrier();

    INIT_STATS();
    START_LOOP_STATS();
    START_STATS();
    vector_sub(src_a, src_b, result, len);
    STOP_STATS();
    END_LOOP_STATS();

    barrier();
    check_result();
}

#ifdef CLUSTER

static void cluster_entry()
{
    pi_cl_team_fork(NUM_CORES, run_test, NULL);
}

static int run_test_on_cluster()
{
    struct pi_cluster_conf cl_conf;
    struct pi_cluster_task cl_task;
    struct pi_device cluster_dev;
    int ret;

    pi_cluster_conf_init(&cl_conf);
    pi_open_from_conf(&cluster_dev, &cl_conf);

    ret = pi_cluster_open(&cluster_dev);
    if (ret) {
#ifdef  ENABLE_LOGGING
        printf("ERROR | Unable to open cluster device\n");
#endif  /* ENABLE_LOGGING */
        goto exit;
    }

    pi_cluster_task(&cl_task, cluster_entry, NULL);
    ret = pi_cluster_send_task_to_cl(&cluster_dev, &cl_task);
    if (ret) {
#ifdef  ENABLE_LOGGING
        printf("ERROR | Unable to send task to cluster controller\n");
#endif  /* ENABLE_LOGGING */
        goto exit;
    }

    pi_cluster_close(&cluster_dev);

exit:
    return ret;
}

static int test_vector_sub()
{
    int ret;

#ifdef  ENABLE_LOGGING
    printf("INFO | Running 'vector_sub' test on PULP Cluster with %d cores\n", NUM_CORES);
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_cluster();

#ifdef  ENABLE_LOGGING
    if (ret)
        printf("ERROR | Unable to run test on cluster\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

#else   /* CLUSTER */

static int run_test_on_fabric()
{
    run_test();
    return 0;
}

static int test_vector_sub()
{
    int ret;

#ifdef  ENABLE_LOGGING
    printf("INFO | Running 'vector_sub' test on Fabric Controller\n");
#endif  /* ENABLE_LOGGING */

    ret = run_test_on_fabric();

#ifdef  ENABLE_LOGGING
    if (ret)
        printf("ERROR | Unable to run test on FC\n");
#endif  /* ENABLE_LOGGING */

    return ret;
}

#endif  /* CLUSTER */

static void test_kickoff()
{
    int ret;

#ifdef  ENABLE_LOGGING
    printf("\n##################################### VECTOR_SUB TEST ####################################\n\n");
#endif  /* ENABLE_LOGGING */

    ret = test_vector_sub();

#ifdef  ENABLE_LOGGING
    printf("\n##########################################################################################\n\n");
#endif  /* ENABLE_LOGGING */

    pmsis_exit(ret);
}

int main()
{
    return pmsis_kickoff(test_kickoff);
}

#endif  /* SPATZ */
