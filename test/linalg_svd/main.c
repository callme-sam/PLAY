#include "data.h"
#include "play.h"
#include "stats.h"
#include "utils.h"

#include <stdbool.h>
#include <math.h>

#include "pmsis.h"

PI_L1 float src[DIM_M * DIM_N];
PI_L1 float mat_V[DIM_N * DIM_N];
PI_L1 float vec_S[DIM_N];
PI_L1 float result[DIM_M * DIM_N];

static void sort_results_descending(float *result, float *mat_V, float *vec_S, const int dim_M, const int dim_N) {
    float tmp;
    int max_idx;

    if (!is_master_core())
        return;

    for (int idx = 0; idx < (dim_N - 1); idx++) {
        max_idx = idx;
        for (int n = (idx + 1); n < dim_N; n++) {
            if (fabs(vec_S[n]) > fabs(vec_S[max_idx]))
                max_idx = n;
        }

        if (max_idx != idx) {
            tmp = vec_S[max_idx];
            vec_S[max_idx] = vec_S[idx];
            vec_S[idx] = tmp;

            for (int m = 0; m < dim_M; m++) {
                tmp = result[m * dim_N + max_idx];
                result[m * dim_N + max_idx] = result[m * dim_N + idx];
                result[m * dim_N + idx] = tmp;
            }

            for (int n = 0; n < dim_N; n++) {
                tmp = mat_V[n * dim_N + max_idx];
                mat_V[n * dim_N + max_idx] = mat_V[n * dim_N + idx];
                mat_V[n * dim_N + idx] = tmp;
            }
        }
    }
}

static void initialize_data()
{
    if (!is_master_core())
        return;

    for (int m = 0; m < DIM_M; m++) {
        for (int n = 0; n < DIM_N; n++) {
            src[m * DIM_N + n] = mat[m * DIM_N + n];
            result[m * DIM_N + n] = 0;
        }
    }

    for (int m = 0; m < DIM_N; m++) {
        for (int n = 0; n < DIM_N; n++) {
            mat_V[m * DIM_N + n] = 0;
        }
    }

    for (int n = 0; n < DIM_N; n++)
        vec_S[n] = 0;
}

static void check_result()
{
    bool test_result;
    bool res_cmp;
    bool s_cmp;
    bool v_cmp;

    if (!is_master_core())
        return;

    res_cmp = matrix_compare_abs(result, expected, DIM_M, DIM_N);
    if (!res_cmp)
        printf("INFO | Result matrix is wrong\n");

    v_cmp = matrix_compare_abs(mat_V, V, DIM_N, DIM_N);
    if (!v_cmp)
        printf("INFO | V matrix is wrong\n");

    s_cmp = vector_compare_abs(vec_S, S, DIM_N);
    if (!s_cmp)
        printf("INFO | S vector is wrong\n");

    test_result = res_cmp && v_cmp && s_cmp;

    matrix_print(src, DIM_M, DIM_M, "mat");
    matrix_print(mat_V, DIM_N, DIM_N, "computed V");
    matrix_print(V, DIM_N, DIM_N, "expected V");
    vector_print(vec_S, DIM_N, "computed S");
    vector_print(S, DIM_N, "expected S");
    matrix_print(result, DIM_M, DIM_N, "result");
    matrix_print(expected, DIM_M, DIM_N, "expected");
    printf("INFO | Test %s\n", test_result ? "SUCCESS" : "FAILED");
}

static void run_test()
{
    initialize_data();
    barrier();

    INIT_STATS();
    START_STATS();
    linalg_svd(src, result, mat_V, vec_S, DIM_M, DIM_N);
    STOP_STATS();
    barrier();
    sort_results_descending(result, mat_V, vec_S, DIM_M, DIM_N);
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

static int test_linalg_svd()
{
    int ret;

    printf("INFO | Running 'linalg_svd' test on PULP Cluster with %d cores\n", NUM_CORES);

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

static int test_linalg_svd()
{
    int ret;

    printf("INFO | Running 'linalg_svd' test on Fabric Controller\n");

    ret = run_test_on_fabric();
    if (ret)
        printf("ERROR | Unable to run test on FC\n");

    return ret;
}

#endif  /* CLUSTER */

static void test_kickoff()
{
    int ret;

    printf("\n##################################### LINALG_SVD TEST ####################################\n\n");
    ret = test_linalg_svd();
    printf("\n##########################################################################################\n\n");
    pmsis_exit(ret);
}

int main()
{
    return pmsis_kickoff(test_kickoff);
}
