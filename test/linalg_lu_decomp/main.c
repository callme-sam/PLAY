#include <stdbool.h>

#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include "pmsis.h"

PI_L1 int perm[DIM_M];
PI_L1 float src[DIM_M * DIM_N];
PI_L1 float result[DIM_M * DIM_N];

static void initialize_data()
{
    if (!is_master_core())
        return;

    for (int m = 0; m < DIM_M; m++){
        for (int n = 0; n < DIM_N; n++) {
            src[m * DIM_N + n] = mat[m * DIM_N + n];
            result[m * DIM_N + n] = 0;
        }
    }

    for (int m = 0; m < DIM_M; m++) {
        perm[m] = 0;
    }
}

static void check_result()
{
    bool test_result;

    if (!is_master_core())
        return;

    test_result = matrix_compare(result, expected_mat, DIM_M, DIM_N);
    if (test_result)
        test_result = vector_compare((float *) perm, (float *) expected_perm, DIM_M);

    matrix_print(src, DIM_M, DIM_N, "src");
    matrix_print(result, DIM_M, DIM_N, "result");
    matrix_print(expected_mat, DIM_M, DIM_N, "expected mat");
    vector_print((float *)perm, DIM_M, "computed permutation");
    vector_print((float *)expected_perm, DIM_M, "expected permutation");
    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void run_test()
{
    initialize_data();
    barrier();

    INIT_STATS();
    START_STATS();
    linalg_lu_decomp(mat, result, perm, DIM_M, DIM_N);
    STOP_STATS();

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

static int test_linalg_lu_decomp()
{
    int ret;

    printf("INFO | Running 'linalg_lu_decomp' test on PULP Cluster with %d cores\n", NUM_CORES);

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

static int test_linalg_lu_decomp()
{
    int ret;

    printf("INFO | Running 'linalg_lu_decomp' test on Fabric Controller\n");

    ret = run_test_on_fabric();
    if (ret)
        printf("ERROR | Unable to run test on FC\n");

    return ret;
}

#endif  /* CLUSTER */

static void test_kickoff()
{
    int ret;

    printf("\n##################################### LINALG_LU_DECOMP TEST ####################################\n\n");
    ret = test_linalg_lu_decomp();
    printf("\n##########################################################################################\n\n");
    pmsis_exit(ret);
}

int main()
{
    return pmsis_kickoff(test_kickoff);
}
