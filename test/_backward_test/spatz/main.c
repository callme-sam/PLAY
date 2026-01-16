#include <stdbool.h>

#include "data.h"

#include "snrt.h"
#include "printf.h"

#define TOLL 0.004f

float *mat __attribute__((aligned(32)));
float *vec __attribute__((aligned(32)));
float *res __attribute__((aligned(32)));
float *exptd __attribute__((aligned(32)));

static int backward_solve_scalar(const float *mat, const float *vec, float *dst, const int dim_M)
{
    float sum;

    for (int m = (dim_M - 1); m >= 0; m--) {
        sum = 0;

        for (int j = m + 1; j < dim_M; j++) {
            sum += mat[m * dim_M + j] * dst[j];
        }

        dst[m] = (vec[m] - sum) / mat[m * dim_M + m];
    }

    return 0;
}

static int backward_solve(const float *mat, const float *vec, float *dst, const int dim_M)
{
    float ZERO_f = 0;

    size_t original_avl;
    size_t avl;
    size_t vl;

    const float *p_mat;
    float *p_dst;

    float sum;

    for (int m = (dim_M - 1); m >= 0; m--) {
        p_mat = mat + m * dim_M + (m + 1);
        p_dst = dst + (m + 1);

        original_avl = dim_M - (m + 1);
        avl = original_avl;

        sum = 0;

        if (avl != 0) {
            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
            asm volatile ("vfmv.v.f v16, %0" :: "f"(ZERO_f));
            asm volatile ("vfmv.v.f v24, %0" :: "f"(ZERO_f));

            for (; avl > 0; avl -= vl) {
                asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

                asm volatile ("vle32.v v8, (%0)" :: "r"(p_dst));
                asm volatile ("vle32.v v0, (%0)" :: "r"(p_mat));
                snrt_cluster_hw_barrier();

                asm volatile ("vfmacc.vv v16, v0, v8");

                p_dst += vl;
                p_mat += vl;
            }

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile ("vfredsum.vs v24, v16, v24");
            asm volatile ("vfmv.f.s %0, v24" : "=f"(sum));
        }

        dst[m] = (vec[m] - sum) / mat[m * dim_M + m];
    }

    return 0;
}

static void initialize_data()
{
    if (snrt_cluster_core_idx() != 0)
        return;

    mat = snrt_l1alloc(DIM_M * DIM_M * sizeof(float));
    vec = snrt_l1alloc(DIM_M * sizeof(float));
    res = snrt_l1alloc(DIM_M * sizeof(float));
    exptd = snrt_l1alloc(DIM_M * sizeof(float));

    for (int m = 0; m < DIM_M; m++){
        for (int n = 0; n < DIM_M; n++)
            mat[m * DIM_M + n] = U[m * DIM_M + n];
    }

    for (int m = 0; m < DIM_M; m++) {
        vec[m] = y[m];
        exptd[m] = expected[m];
        res[m] = 0;
    }
}

static bool vector_compare(const float *vec_a, const float *vec_b, const int len)
{
    float abs_diff;
    bool ret;

    ret = true;
    for (int i = 0; i < len; i++) {
        abs_diff = fabs(vec_a[i] - vec_b[i]);
        if (abs_diff > TOLL) {
            printf("idx: %d - abs_diff: %f - vec_a: %f - vec_b: %f\n", i, abs_diff, vec_a[i], vec_b[i]);
            ret = false;
        }
    }

    return ret;
}

static void check_res()
{
    bool test_res;

    if (snrt_cluster_core_idx() != 0)
        return;

    test_res = vector_compare(res, exptd, DIM_M);

    printf("INFO | Test %s\n", test_res ? "SUCCESS" : "FAILED");
}

static void run_test()
{
    volatile int m = DIM_M;

    initialize_data();
    snrt_cluster_hw_barrier();

    backward_solve(mat, vec, res, m);

    snrt_cluster_hw_barrier();
    check_res();
}

static int run_test_on_spatz()
{
    run_test();
    return 0;
}

static int test_backward_solve()
{
    int ret;

    if (snrt_cluster_core_idx() == 0) printf("INFO | Running 'backward_solve' test on Spatz Cluster with %d Core Compelx\n", NUM_CC);

    ret = run_test_on_spatz();

    return ret;
}

static int test_kickoff()
{
    int ret;

    if (snrt_cluster_core_idx() == 0) printf("\n##################################### BACKWARD_SOLVE TEST ####################################\n\n");

    ret = test_backward_solve();

    if (snrt_cluster_core_idx() == 0) printf("\n##########################################################################################\n\n");

    return ret;
}

int main()
{
    return test_kickoff();
}
