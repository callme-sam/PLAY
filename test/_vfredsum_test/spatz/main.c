#include "snrt.h"
#include "printf.h"

#include <math.h>
#include <stdbool.h>

#include "data.h"

#define TOLL 0.004f

float *src __attribute__((aligned(32)));
float *result;
float *expected;

static void init_data()
{
    src = snrt_l1alloc(LEN * sizeof(float));
    result = snrt_l1alloc(sizeof(float));
    expected = snrt_l1alloc(sizeof(float));

    for (int i = 0; i < LEN; i++)
        src[i] = input_data[i];

    *result = 0;
    *expected = 0;
}

static void manual_reduction()
{
    for (int i = 0; i < LEN; i++)
        *expected += src[i];
}

static void rvv_reduction()
{
    float ZERO_f = 0.0f;
    size_t original_avl;
    size_t avl;
    size_t vl;
    float *v;

    original_avl = LEN;
    avl = original_avl;
    v = src;

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vfmv.v.f v0, %0" :: "f"(ZERO_f));
    asm volatile ("vfmv.v.f v8, %0" :: "f"(ZERO_f));

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m1, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vle32.v v16, (%0)" :: "r"(v));
        asm volatile ("vfredsum.vs v8, v16, v8");
        snrt_cluster_hw_barrier();

        v += vl;
    }

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(original_avl));
    asm volatile ("vfmv.f.s %0, v8" : "=f"(*result));
}

static void check_result()
{
    float abs_diff;

    abs_diff = fabs(*result - *expected);
    if (abs_diff < TOLL)
        printf("Test PASSED!\n");
    else
        printf("Test FAILED! abs diff: %f\n", abs_diff);
}

int main()
{
    printf("######################################## vfredusum TEST ###############################################\n\n");

    init_data();
    manual_reduction();
    rvv_reduction();
    check_result();

    printf("\n##########################################################################################################\n\n");

    return 0;
}
