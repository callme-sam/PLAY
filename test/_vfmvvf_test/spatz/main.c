#include "snrt.h"
#include "printf.h"

#define LEN 8

float *vec;

__attribute__((noinline)) static void print_data()
{
    for (int i = 0; i < LEN; i++)
        printf("%f ", vec[i]);
    printf("\n");
}

__attribute__((noinline)) static void init_data()
{
    vec = snrt_l1alloc(LEN * sizeof(float));

    for (int i = 0; i < LEN; i++) {
        vec[i] = 1;
    }
}

__attribute__((noinline)) static void test_vfmvvf()
{
    size_t avl;
    size_t vl;

    avl = LEN;
    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    snrt_cluster_hw_barrier();
    asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0));
    snrt_cluster_hw_barrier();
    asm volatile ("vse32.v v0, (%0)" :: "r"(vec));
    snrt_cluster_hw_barrier();
}

int main()
{
    printf("################################### Testing vfmv.v.f #######################################\n");

    init_data();
    print_data();
    test_vfmvvf();
    print_data();

    printf("############################################################################################\n");

    return 0;
}
