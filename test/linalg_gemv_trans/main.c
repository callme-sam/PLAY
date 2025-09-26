#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "pmsis.h"

PI_L1 float beta;
PI_L1 float alpha;
PI_L1 float vec_x[DIM_M] __attribute__((aligned(4)));
PI_L1 float vec_y[DIM_N] __attribute__((aligned(4)));
PI_L1 float result[DIM_N] __attribute__((aligned(4)));
PI_L1 float mat[DIM_M * DIM_N] __attribute__((aligned(4)));

static void initialize_data()
{
    if (!is_master_core())
        return;

    for (int m = 0; m < DIM_M; m++)
        for (int n = 0; n < DIM_N; n++)
            mat[m * DIM_N + n] = matA[m * DIM_N + n];

    for (int n= 0; n < DIM_N; n++) {
        vec_y[n] = vecY[n];
        result[n] = 0;
    }

    for (int m = 0; m < DIM_M; m++)
        vec_x[m] = vecX[m];

    alpha = a;
    beta = b;
}

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = vector_compare(result, expected, DIM_N);

    scalar_print(alpha, "alpha");
    scalar_print(beta, "beta");
    vector_print(vec_x, DIM_M, "vec_x");
    vector_print(vec_y, DIM_N, "vec_y");
    matrix_print(mat, DIM_M, DIM_N, "mat");
    vector_print(result, DIM_N, "result");
    vector_print(expected, DIM_N, "expected");
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
    linalg_gemv_trans(mat, vec_x, vec_y, alpha, beta, result, m, n);
    STOP_STATS();
    END_LOOP_STATS();

    barrier();
    check_result();
}

#ifdef  CLUSTER

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

static int test_linalg_gemv_trans()
{
    int ret;

    printf("INFO | Running 'linalg_gemv_trans' test on PULP Cluster with %d cores\n", NUM_CORES);

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

static int test_linalg_gemv_trans()
{
    int ret;

    printf("INFO | Running 'linalg_gemv_trans' test on Fabric Controller\n");

    ret = run_test_on_fabric();
    if (ret)
        printf("ERROR | Unable to run test on FC\n");

    return ret;
}

#endif  /* CLUSTER */

static void test_kickoff()
{
    int ret;

    printf("\n##################################### LINALG_GEMV_TRANS TEST ####################################\n\n");
    ret = test_linalg_gemv_trans();
    printf("\n##########################################################################################\n\n");
    pmsis_exit(ret);
}

int main()
{
    return pmsis_kickoff(test_kickoff);
}
