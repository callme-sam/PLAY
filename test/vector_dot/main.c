#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "pmsis.h"

PI_L1 float src_a[LEN] __attribute__((aligned(4)));
PI_L1 float src_b[LEN] __attribute__((aligned(4)));
PI_L1 float result;

static void initialize_vectors()
{
    if (!is_master_core())
        return;

    result = 0;
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

    test_result = scalar_compare(result, expected);

    vector_print(src_a, LEN, "src_a");
    vector_print(src_b, LEN, "src_b");
    scalar_print(result, "result");
    scalar_print(expected, "expected");
    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void run_test()
{
    volatile int len = LEN;
    initialize_vectors();
    barrier();

    INIT_STATS();
    START_STATS();
    vector_dot(src_a, src_b, &result, len);
    STOP_STATS();

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
        printf("ERROR | Unable to open cluster device\n");
        goto exit;
    }

    pi_cluster_task(&cl_task, cluster_entry, NULL);
    ret = pi_cluster_send_task_to_cl(&cluster_dev, &cl_task);
    if (ret) {
        printf("ERROR | Unable to send task to cluster controller\n");
        goto exit;
    }

    pi_cluster_close(&cluster_dev);

exit:
    return ret;
}

static int test_vector_dot()
{
    int ret;

    printf("INFO | Running 'vector_dot' test on PULP Cluster with %d cores\n", NUM_CORES);

    ret = run_test_on_cluster();
    if (ret)
        printf("ERROR | Unable to run test on cluster\n");

    return ret;
}

#else   /* CLUSTER */

static int run_test_on_fabric()
{
    run_test();
    return 0;
}

static int test_vector_dot()
{
    int ret;

    printf("INFO | Running 'vector_dot' test on Fabric Controller\n");

    ret = run_test_on_fabric();
    if (ret)
        printf("ERROR | Unable to run test on FC\n");

    return ret;
}

#endif  /* CLUSTER */

static void test_kickoff()
{
    int ret;

    printf("\n##################################### VECTOR_DOT TEST ####################################\n\n");
    ret = test_vector_dot();
    printf("\n##########################################################################################\n\n");
    pmsis_exit(ret);
}

int main()
{
    return pmsis_kickoff(test_kickoff);
}
