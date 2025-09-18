#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "pmsis.h"

PI_L1 float src[DIM_M * DIM_M] __attribute__((aligned(4)));
PI_L1 float mat_V[DIM_M * DIM_M] __attribute__((aligned(4)));
PI_L1 float vec_S[DIM_M] __attribute__((aligned(4)));
PI_L1 float result[DIM_M * DIM_M] __attribute__((aligned(4)));

static void sort_results_descending(float *result, float *mat_V, float *vec_S, const int dim_M) {
    float tmp;
    int max_idx;

    if (!is_master_core())
        return;

    for (int i = 0; i < (dim_M - 1); i++) {
        max_idx = i;
        for (int j = (i + 1); j < dim_M; j++) {
            if (fabs(vec_S[j]) > fabs(vec_S[max_idx])) {
                max_idx = j;
            }
        }

        if (max_idx != i) {
            tmp = vec_S[i];
            vec_S[i] = vec_S[max_idx];
            vec_S[max_idx] = tmp;

            tmp = result[i * dim_M + i];
            result[i * dim_M + i] = result[max_idx * dim_M + max_idx];
            result[max_idx * dim_M + max_idx] = tmp;

            for (int k = 0; k < dim_M; k++) {
                tmp = mat_V[k * dim_M + i];
                mat_V[k * dim_M + i] = mat_V[k * dim_M + max_idx];
                mat_V[k * dim_M + max_idx] = tmp;
            }
        }
    }
}

static void initialize_data()
{
    if (!is_master_core())
        return;

    for (int m = 0; m < DIM_M; m++) {
        for (int n = 0; n < DIM_M; n++) {
            src[m * DIM_M + n] = mat[m * DIM_M + n];
            mat_V[m * DIM_M + n] = 0;
            result[m * DIM_M + n] = 0;
        }
    }

    for (int m = 0; m < DIM_M; m++)
        vec_S[m] = 0;

}

static void check_result()
{
    bool test_result;
    bool res_cmp;
    bool s_cmp;
    bool v_cmp;

    if (!is_master_core())
        return;

    res_cmp = matrix_compare_abs(result, expected, DIM_M, DIM_M);
    if (!res_cmp)
        printf("INFO | Result matrix is wrong\n");

    v_cmp = matrix_compare_abs(mat_V, V, DIM_M, DIM_M);
    if (!v_cmp)
        printf("INFO | V matrix is wrong\n");

    s_cmp = vector_compare_abs(vec_S, S, DIM_M);
    if (!s_cmp)
        printf("INFO | S vector is wrong\n");

    test_result = res_cmp && v_cmp && s_cmp;

    matrix_print(src, DIM_M, DIM_M, "mat");
    matrix_print(mat_V, DIM_M, DIM_M, "computed V");
    matrix_print(V, DIM_M, DIM_M, "expected V");
    vector_print(vec_S, DIM_M, "computed S");
    vector_print(S, DIM_M, "expected S");
    matrix_print(result, DIM_M, DIM_M, "result");
    matrix_print(expected, DIM_M, DIM_M, "expected");
    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void run_test()
{
    volatile int m = DIM_M;
    initialize_data();
    barrier();

    INIT_STATS();
    START_STATS();
    linalg_svd_jacobi(src, result, mat_V, vec_S, m);
    STOP_STATS();
    barrier();
    sort_results_descending(result, mat_V, vec_S, DIM_M);
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

static int test_linalg_svd_jacobi()
{
    int ret;

    printf("INFO | Running 'linalg_svd_jacobi' test on PULP Cluster with %d cores\n", NUM_CORES);

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

static int test_linalg_svd_jacobi()
{
    int ret;

    printf("INFO | Running 'linalg_svd_jacobi' test on Fabric Controller\n");

    ret = run_test_on_fabric();
    if (ret)
        printf("ERROR | Unable to run test on FC\n");

    return ret;
}

#endif  /* CLUSTER */

static void test_kickoff()
{
    int ret;

    printf("\n##################################### LINALG_SVD_JACOBI TEST ####################################\n\n");
    ret = test_linalg_svd_jacobi();
    printf("\n##########################################################################################\n\n");
    pmsis_exit(ret);
}

int main()
{
    return pmsis_kickoff(test_kickoff);
}
