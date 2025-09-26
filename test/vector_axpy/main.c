#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "pmsis.h"

PI_L1 float src_a[LEN] __attribute__((aligned(4)));
PI_L1 float src_b[LEN] __attribute__((aligned(4)));
PI_L1 float alpha;
PI_L1 float result[LEN] __attribute__((aligned(4)));

static void initialize_vectors()
{
    if (!is_master_core())
        return;

    alpha = scalar;
    for (int i = 0; i < LEN; i++) {
        src_a[i] = vec_a[i];
        src_b[i] = vec_b[i];
        result[i] = 0;
    }
}

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = vector_compare(result, expected, LEN);

    vector_print(src_a, LEN, "src_a");
    vector_print(src_b, LEN, "src_b");
    scalar_print(alpha, "alpha");
    vector_print(result, LEN, "result");
    vector_print(expected, LEN, "expected");
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
    vector_axpy(src_a, src_b, alpha, result, len);
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

static int test_vector_axpy()
{
    int ret;

    printf("INFO | Running 'vector_axpy' test on PULP Cluster with %d cores\n", NUM_CORES);

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

static int test_vector_axpy()
{
    int ret;

    printf("INFO | Running 'vector_axpy' test on Fabric Controller\n");

    ret = run_test_on_fabric();
    if (ret)
        printf("ERROR | Unable to run test on FC\n");

    return ret;
}

#endif  /* CLUSTER */

static void test_kickoff()
{
    int ret;

    printf("\n##################################### VECTOR_AXPY TEST ####################################\n\n");
    ret = test_vector_axpy();
    printf("\n##########################################################################################\n\n");
    pmsis_exit(ret);
}

int main()
{
    return pmsis_kickoff(test_kickoff);
}
