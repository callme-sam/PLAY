#include <stdbool.h>
#include <math.h>

#include "data.h"

#include "snrt.h"
#include "printf.h"

#define MAX_LEN 1024
#define TOL 1e-3

#define NUM_TESTS 4
int sweep[NUM_TESTS] = {16, 64, 512, 1024};

static void fill_array(float *vec, const int len)
{
    for (int i = 0; i < len; i++) {
        vec[i] = vec_a[i];
    }
}

static float vector_vfmv(const float *vec, const int len)
{
    const float *v;
    float result;
    size_t avl;
    size_t vl;

    result = 42;
    avl = len;
    v = vec;

    asm volatile ("vsetvli %0, %1, e32, m1, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vle32.v v1, (%0)" :: "r"(v));

#if 1
    asm volatile ("vfmv.f.s %0, v1" : "=f"(result));
#else
    asm volatile ("vfmv.f.s f1, v1" ::: "f1");
    asm volatile ("fsw f1, (%0)" :: "r"(&result));
#endif

    snrt_cluster_hw_barrier();
    return result;
}

int main()
{
    float data[MAX_LEN]__attribute__((aligned(32)));

    for (int test = 0; test < NUM_TESTS; test++) {
        printf("######################################## TEST %d ###############################################\n\n", test + 1);

        float expected;
        float computed;
        float abs_diff;
        bool passed;
        int len;

        len = sweep[test];
        fill_array(data, len);

        expected = data[0];
        computed = vector_vfmv(data, len);

        abs_diff = fabs(computed - expected);
        passed = abs_diff < TOL ? true : false;

        printf("len = %d\n", len);
        printf("expected: %.4f\n", expected);
        printf("computed: %.4f\n", computed);
        if (passed) {
            printf("==> SUCCESS\n");
        } else {
            printf("==> FAILED - abs diff: %f\n", abs_diff);
        }

        printf("\n#################################################################################################\n");
    }

    return 0;
}
