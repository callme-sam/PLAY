#include "snrt.h"
#include "printf.h"

#include <math.h>
#include <stdbool.h>

#define LEN 16
#define TOLL 0.004f

float alpha;
float *src_a __attribute__((aligned(32)));
float *src_b __attribute__((aligned(32)));
float *result __attribute__((aligned(32)));
float *expected __attribute__((aligned(32)));

void init_data()
{

    src_a = snrt_l1alloc(LEN * sizeof(float));
    src_b = snrt_l1alloc(LEN * sizeof(float));
    result = snrt_l1alloc(LEN * sizeof(float));
    expected = snrt_l1alloc(LEN * sizeof(float));

    for (int i = 0; i < LEN; i++) {
        src_a[i] = (float)i;
        src_b[i] = (float)(i / 10.0f);
        result[i] = 0;
        expected[i] = 0;
    }

    alpha = 0.5f;
}

void compute_expected()
{
    for (int i = 0; i < LEN; i++)
        expected[i] = (src_a[i] * alpha) + src_b[i];
}

void print_vector(float *vec, char *name)
{
    printf("printing %s\n", name);
    for (int i = 0; i < LEN; i++)
        printf("%6.2f ", vec[i]);
    printf("\n");
}

void print_input()
{
    print_vector(src_a, "src_a");
    print_vector(src_b, "src_b");
}

void check_result()
{
    bool res;
    float abs_diff;

    res = true;
    for (int i = 0; i < LEN; i++) {
        abs_diff = fabs(result[i] - expected[i]);
        if (abs_diff > TOLL) {
            res = false;
            printf("Error at idx %d - abs diff=%6.2f\n", i, abs_diff);
        }
    }

    printf("Test %s\n", res ? "SUCCESS" : "FAILED");
}

void test_vfmacc()
{
    uint64_t start;
    uint64_t end;

    float scalar;

    size_t avl;
    size_t vl;

    avl = LEN;
    scalar = alpha;


    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    printf("\nTesting mul + add\n");

    asm volatile ("vle32.v v0, (%0)" :: "r"(src_a));
    asm volatile ("vle32.v v8, (%0)" :: "r"(src_b));

    start = read_csr(mcycle);
    asm volatile ("vfmul.vf v16, v0, %0" :: "f"(scalar));
    asm volatile ("vfadd.vv v24, v16, v8");
    asm volatile ("vse32.v v24, (%0)" :: "r"(result));
    end = read_csr(mcycle);

    check_result();
    printf("took %llu cycles\n", end - start);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    printf("\nTesting mul + add same register\n");

    asm volatile ("vle32.v v0, (%0)" :: "r"(src_a));
    asm volatile ("vle32.v v8, (%0)" :: "r"(src_b));

    start = read_csr(mcycle);
    asm volatile ("vfmul.vf v0, v0, %0" :: "f"(scalar));
    asm volatile ("vfadd.vv v0, v0, v8");
    asm volatile ("vse32.v v0, (%0)" :: "r"(result));
    end = read_csr(mcycle);

    check_result();
    printf("took %llu cycles\n", end - start);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    printf("\nTesting macc\n");

    asm volatile ("vle32.v v0, (%0)" :: "r"(src_a));
    asm volatile ("vle32.v v8, (%0)" :: "r"(src_b));

    start = read_csr(mcycle);
    asm volatile ("vfmacc.vf v8, %0, v0" :: "f"(scalar));
    asm volatile ("vse32.v v8, (%0)" :: "r"(result));
    end = read_csr(mcycle);

    check_result();
    printf("took %llu cycles\n", end - start);

}


int main()
{
    printf("################################### Testing vfmacc ########################################\n");

    init_data();
    compute_expected();
    // print_input();
    test_vfmacc();

    printf("############################################################################################\n");

    return 0;
}
