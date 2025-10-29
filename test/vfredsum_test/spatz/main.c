#include <math.h>
#include <stdbool.h>

#include "data.h"
#include "utils.h"

#include "snrt.h"
#include "printf.h"

#define MAX_LEN 1024
#define NUM_TESTS 4
#define TOL 1e-3

int sweep[NUM_TESTS] = {16, 64, 512, 1024};

static void fill_array(float *vec, const int len)
{
    for (int i = 0; i < len; i++) {
        vec[i] = vec_a[i];
    }
}

static float manual_reduction(const float *vec, const int len)
{
    float red;

    red = 0;
    for (int i = 0; i < len; i++) {
        red += vec[i];
    }

    return red;
}

#if 0

static float vector_reduction(const float *vec, const int len)
{
    const float *v;
    float result;
    size_t avl;
    size_t vl;
    int cnt;

    result = 0.0f;
    avl = len;
    v = vec;
    cnt = 0;

    asm volatile ("vsetvli %0, %1, e32, m1, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

    for (; avl > 0; avl -= vl) {
        float acc;

        asm volatile ("vsetvli %0, %1, e32, m1, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vle32.v v1, (%0)" :: "r"(v));
        asm volatile ("vfredsum.vs v1, v1, v0");
        asm volatile ("vfmv.f.s %0, v1" : "=f"(acc));

        result += acc;
        v += vl;
        cnt++;
    }

    printf("Iterated for %d cycles\n", cnt);
    return result;
}

#else

static float vector_reduction(const float *vec, const int len)
{
    const float *v;
    float result;
    size_t avl;
    size_t vl;
    int cnt;

    result = 0.0f;
    avl = len;
    v = vec;
    cnt = 0;

    asm volatile ("vsetvli %0, %1, e32, m1, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0));
    asm volatile ("vfmv.v.f v3, %0" :: "f"(0.0));

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m1, ta, ma" : "=r"(vl) : "r"(avl));

        float tmp[vl];

        asm volatile ("vle32.v v1, (%0)" :: "r"(v));

        asm volatile ("vfredsum.vs v3, v1, v0");

        asm volatile ("vse32.v v3, (%0)" :: "r"(tmp));
        snrt_cluster_hw_barrier();

        result += tmp[0];
        v += vl;
        cnt++;
    }

    printf("Iterated for %d cycles\n", cnt);
    return result;
}

#endif


int main()
{
    for (int test = 0; test < NUM_TESTS; test++) {
        printf("######################################## TEST %d ###############################################\n\n", test);

        float expected;
        float computed;
        float abs_diff;
        bool passed;
        int len;

        len = sweep[test];
        printf("len = %d\n", len);

        float data[len];
        fill_array(data, len);

        expected = manual_reduction(data, len);
        computed = vector_reduction(data, len);

        abs_diff = fabs(computed - expected);
        passed = abs_diff < TOL ? true : false;

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
