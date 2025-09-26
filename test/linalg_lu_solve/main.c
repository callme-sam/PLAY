#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "pmsis.h"

PI_L1 float mat[DIM_M * DIM_M] __attribute__((aligned(4)));
PI_L1 float vec[DIM_M] __attribute__((aligned(4)));
PI_L1 int perm[DIM_M] __attribute__((aligned(4)));
PI_L1 float result[DIM_M] __attribute__((aligned(4)));

static void initialize_data()
{
    if (!is_master_core())
        return;

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

    matrix_print(mat, DIM_M, DIM_M, "mat");
    vector_print((float *)perm, DIM_M, "perm");
    vector_print(vec, DIM_M, "vec");
    vector_print(result, DIM_M, "result");
    vector_print(expected, DIM_M, "expected");
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

static int test_linalg_lu_solve()
{
    int ret;

    printf("INFO | Running 'linalg_lu_solve' test on PULP Cluster with %d cores\n", NUM_CORES);

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

static int test_linalg_lu_solve()
{
    int ret;

    printf("INFO | Running 'linalg_lu_solve' test on Fabric Controller\n");

    ret = run_test_on_fabric();
    if (ret)
        printf("ERROR | Unable to run test on FC\n");

    return ret;
}

#endif  /* CLUSTER */

static void test_kickoff()
{
    int ret;

    printf("\n##################################### LINALG_LU_SOLVE TEST ####################################\n\n");
    ret = test_linalg_lu_solve();
    printf("\n##########################################################################################\n\n");
    pmsis_exit(ret);
}

int main()
{
    return pmsis_kickoff(test_kickoff);
}
