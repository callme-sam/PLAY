#include <stdbool.h>

#include "snrt.h"
#include "printf.h"

#define DIM_M   64
#define DIM_N   10

float *input_data __attribute__((aligned(32)));
float *expected __attribute__((aligned(32)));
float *result __attribute__((aligned(32)));

static void init_data()
{
    printf("Initializing data...");

    input_data = snrt_l1alloc(DIM_M * DIM_N * sizeof(float));
    if (!input_data) {
        printf("Error allocating memory for input data\n");
        snrt_exit(-1);
    }

    expected = snrt_l1alloc(DIM_M * sizeof(float));
    if (!expected) {
        printf("Error allocating memory for expected data\n");
        snrt_exit(-1);
    }

    result = snrt_l1alloc(DIM_M * sizeof(float));
    if (!result) {
        printf("Error allocating memory for result data\n");
        snrt_exit(-1);
    }

    for (int m = 0; m < DIM_M; m++) {
        for (int n = 0; n < DIM_N; n++) {
            input_data[m * DIM_N + n] = ((float)(m * 10 + n)) / 100.0;
        }
    }

    for (int m = 0; m < DIM_M; m++) {
        expected[m] = input_data[m * DIM_N];
        result[m] = 0;
    }

    printf(" done!\n");

    printf("Matrix:\n");
    printf("[\n");
    for (int r = 0; r < DIM_M; r++) {
        for (int c = 0; c < (DIM_N - 1); c++)
            printf("%06.2f,  ", input_data[r * DIM_N + c]);
        printf("%06.2f;\n", input_data[r * DIM_N + (DIM_N - 1)]);
    }
    printf("]\n");
}

static void test_vlse()
{
    printf("Starting test...\n");

    size_t stride;
    size_t avl;
    size_t vl;
    size_t it;

    float *output;
    float *input;

    stride = DIM_N * sizeof(float);
    input = input_data;
    output = result;
    avl = DIM_M;
    it = 0;

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m1, ta, ma" : "=r"(vl) : "r"(avl));
        asm volatile ("vlse32.v v0, (%0), %1" :: "r"(input), "r"(stride));
        asm volatile ("vse32.v v0, (%0)" :: "r"(output));
        snrt_cluster_hw_barrier();

        input += vl * DIM_N;
        output += vl;

        printf("%u) vl = %u\n", it, vl);
        it++;
    }

    printf(" done!\n");
}

static void check_result()
{
    printf("Checking result...\n");

    bool check;

    check = true;
    for (int m = 0; m < DIM_M; m++) {
        printf("idx:%d - result=%06.2f - expected=%06.2f --> ", m, result[m], expected[m]);
        if (result[m] != expected[m]) {
            check = false;
            printf("ERROR\n");
        } else {
            printf("OK\n");
        }
    }

    if (check)
        printf("Test SUCCESS\n");
    else
        printf("Test FAILED\n");
}

int main()
{
    init_data();
    test_vlse();
    check_result();

    return 0;
}
