#include "snrt.h"
#include "printf.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define DIM 8


void test_vmfgt(float *vec_A, float scalar_B, int *vec_M, int dim) {
    int vl;

    float *ptr_A = vec_A;
    int *ptr_M = vec_M;
    int avl = dim;

    for (; avl > 0; avl -= vl) {
        printf("about to vsetvli\n");
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        printf("about to vle32.v\n");
        asm volatile ("vle32.v v0, (%0)" :: "r"(ptr_A));

        printf("about to vmfgt\n");
        asm volatile ("vmfgt.vf v1, v0, %0" :: "f"(scalar_B));

        printf("about to vmsbf\n");
        asm volatile ("vmsbf.m v16, v1");

        printf("about to vse32.v\n");
        asm volatile ("vse32.v v16, (%0)" :: "r"(ptr_M));

        ptr_A += vl;
        ptr_M += vl;
    }
}

int main() {
    float A[DIM] = {10.0f, 5.0f, 15.0f, 0.0f, 20.0f, 5.0f, -1.0f, 8.0f};
    float B = 8.0f;
    int M[DIM] = {0};
    int E[DIM] = {1, 0, 1, 0, 1, 0, 0, 0};

    printf("--- Test vmfgt.vf: Vector A > Scalar B (8.0) ---\n");

    test_vmfgt(A, B, M, DIM);

    bool pass = true;
    for (int i = 0; i < DIM; i++) {
        if (M[i] != E[i])
            pass = false;
    }

    printf("Test %s\n", pass ? "SUCCEDD" : "FAILED");

    return 0;
}
