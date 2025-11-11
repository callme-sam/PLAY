#include "snrt.h"
#include "printf.h"

#if DOUBLE_PRECISION
typedef double VAR_T;
#define VAR_T_FMT "%lf"
#define TYPE "DOUBLE"
#define FDIV_INSTR "fdiv.d"
#else
typedef float VAR_T;
#define VAR_T_FMT "%f"
#define TYPE "FLOAT"
#define FDIV_INSTR "fdiv.s"
#endif

__attribute__((noinline)) static void print_data(VAR_T val_a, VAR_T val_b, VAR_T result)
{
    printf("val_a=" VAR_T_FMT "\n", val_a);
    printf("val_b=" VAR_T_FMT "\n", val_b);
    printf("result=" VAR_T_FMT "\n", result);
}

__attribute__((noinline)) static void init_data(VAR_T *val_a, VAR_T *val_b, VAR_T *result)
{
    *val_a = 0.01;
    *val_b = 0.001;
    *result = 0;
}

__attribute__((noinline)) static void test_fdiv(VAR_T val_a, VAR_T val_b, VAR_T *result)
{
    printf("About to enter div\n");
    snrt_cluster_hw_barrier();
    asm volatile (FDIV_INSTR " %0, %1, %2" : "=f"(*result) : "f"(val_a), "f"(val_b));
}

int main()
{
    printf("################################### Testing fdiv using %s ##################################\n", TYPE);

    VAR_T val_a;
    VAR_T val_b;
    VAR_T result;

    init_data(&val_a, &val_b, &result);
    print_data(val_a, val_b, result);
    test_fdiv(val_a, val_b, &result);
    print_data(val_a, val_b, result);

    printf("############################################################################################\n", TYPE);

    return 0;
}
