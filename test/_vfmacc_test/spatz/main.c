#include "snrt.h"
#include "printf.h"

#include <math.h>
#include <stdbool.h>

#define LEN 128
#define TOLL 0.004f

#ifdef MUL_ADD
    const char instr[] = "MUL + ADD";
#elif defined MUL_ADD_REUSE
    const char instr[] = "MUL + ADD WITH REUSE";
#elif defined MACC
    const char instr[] = "MACC";
#else
    #error "No Instruction selected"
#endif

#ifdef LOOP
    const char loop[] = "Loop";
#else
    const char loop[] = "NO-Loop";
#endif

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

void check_result(int up_to)
{
    bool res;
    float abs_diff;

    res = true;
    for (int i = 0; i < up_to; i++) {
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
    size_t avl;
    size_t vl;

    uint64_t start;
    uint64_t end;
    float scalar;

    const float *a;
    const float *b;
    float *r;

    scalar = alpha;
    r = result;
    a = src_a;
    b = src_b;
    avl = LEN;

    start = read_csr(mcycle);

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

    asm volatile ("vle32.v v0, (%0)" :: "r"(a));
    asm volatile ("vle32.v v8, (%0)" :: "r"(b));

#ifdef MUL_ADD
    /* len 4:       21 cycl */
    /* len 128:     21 cycl */
    /* len 256:     21 cycl */
    /* len 2048:    21 cycl*/
    asm volatile ("vfmul.vf v16, v0, %0" :: "f"(scalar));
    asm volatile ("vfadd.vv v24, v16, v8");
    asm volatile ("vse32.v v24, (%0)" :: "r"(r));
#elif defined MUL_ADD_REUSE
    /* len 4:       21 cycl */
    /* len 128:     21 cycl */
    /* len 256:     21 cycl */
    /* len 2048:    21 cycl */
    asm volatile ("vfmul.vf v0, v0, %0" :: "f"(scalar));
    asm volatile ("vfadd.vv v0, v0, v8");
    asm volatile ("vse32.v v0, (%0)" :: "r"(r));
#elif defined MACC
    /* len 4:       38 cycl */
    /* len 128:     38 cycl */
    /* len 256:     38 cycl */
    /* len 2048:    38 cycl */
    asm volatile ("vfmacc.vf v8, %0, v0" :: "f"(alpha));
    asm volatile ("vse32.v v8, (%0)" :: "r"(r));
#endif

    end = read_csr(mcycle);

    check_result(vl);
    printf("took %llu cycles\n", end - start);
}

void test_vfmacc_v0()
{
    uint64_t start;
    uint64_t end;

    float scalar;

    size_t avl;
    size_t vl;

    avl = LEN;
    scalar = alpha;


    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

#ifdef MUL_ADD
    /**
     * len 128
     * total    -> 68   (62 with barriers)
     * loads    -> 47   (41 with barriers)
     * instr    -> 3    (3 with barriers)
     * store    -> 20   (22 with barriers)
     */
    snrt_cluster_hw_barrier();
    start = read_csr(mcycle);
    asm volatile ("vle32.v v0, (%0)" :: "r"(src_a));
    asm volatile ("vle32.v v8, (%0)" :: "r"(src_b));

    asm volatile ("vfmul.vf v16, v0, %0" :: "f"(scalar));
    asm volatile ("vfadd.vv v24, v16, v8");

    asm volatile ("vse32.v v24, (%0)" :: "r"(result));
    end = read_csr(mcycle);
    snrt_cluster_hw_barrier();

#elif defined MUL_ADD_REUSE
    /**
     * len 128
     * total    -> 68   (62 with barriers)
     * loads    -> 47   (41 with barriers)
     * instr    -> 3    (3 with barriers)
     * store    -> 20   (22 with barriers)
     */
    snrt_cluster_hw_barrier();
    start = read_csr(mcycle);
    asm volatile ("vle32.v v0, (%0)" :: "r"(src_a));
    asm volatile ("vle32.v v8, (%0)" :: "r"(src_b));

    asm volatile ("vfmul.vf v0, v0, %0" :: "f"(scalar));
    asm volatile ("vfadd.vv v0, v0, v8");
    asm volatile ("vse32.v v0, (%0)" :: "r"(result));
    end = read_csr(mcycle);
    snrt_cluster_hw_barrier();

#elif defined MACC
    /**
     * len 128
     * total    -> 67   (61 with barriers)
     * loads    -> 40   (41 with barriers)
     * instr    -> 2    (2 with barriers)
     * store    -> 20   (21 with barriers)
     */
    snrt_cluster_hw_barrier();
    start = read_csr(mcycle);
    asm volatile ("vle32.v v0, (%0)" :: "r"(src_a));
    asm volatile ("vle32.v v8, (%0)" :: "r"(src_b));

    asm volatile ("vfmacc.vf v8, %0, v0" :: "f"(scalar));

    asm volatile ("vse32.v v8, (%0)" :: "r"(result));
    end = read_csr(mcycle);
    snrt_cluster_hw_barrier();
#endif

    check_result(vl);
    printf("took %llu cycles\n", end - start);

}

void test_vfmacc_pointers_on_l2()
{
    size_t avl;
    size_t vl;

    uint64_t start;
    uint64_t end;
    float scalar;

    scalar = alpha;
    avl = LEN;

    start = read_csr(mcycle);

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

    asm volatile ("vle32.v v0, (%0)" :: "r"(src_a));
    asm volatile ("vle32.v v8, (%0)" :: "r"(src_b));

#ifdef MUL_ADD
    /* len 4:        70 cycl */
    /* len 128:      70 cycl */
    /* len 256:      70 cycl */
    /* len 2048:     cycl*/
    asm volatile ("vfmul.vf v16, v0, %0" :: "f"(scalar));
    asm volatile ("vfadd.vv v24, v16, v8");
    asm volatile ("vse32.v v24, (%0)" :: "r"(result));
#elif defined MUL_ADD_REUSE
    /* len 4:        70 cycl */
    /* len 128:      70 cycl */
    /* len 256:      70 cycl */
    /* len 2048:     cycl */
    asm volatile ("vfmul.vf v0, v0, %0" :: "f"(scalar));
    asm volatile ("vfadd.vv v0, v0, v8");
    asm volatile ("vse32.v v0, (%0)" :: "r"(result));
#elif defined MACC
    /* len 4:        79 cycl */
    /* len 128:      79 cycl */
    /* len 256:      79 cycl */
    /* len 2048:     cycl */
    asm volatile ("vfmacc.vf v8, %0, v0" :: "f"(alpha));
    asm volatile ("vse32.v v8, (%0)" :: "r"(result));
#endif

    end = read_csr(mcycle);

    check_result(vl);
    printf("took %llu cycles\n", end - start);
}

void test_vfmacc_loop()
{
    size_t avl;
    size_t vl;

    uint64_t start;
    uint64_t end;
    float scalar;

    const float *a;
    const float *b;
    float *r;

    scalar = alpha;
    r = result;
    a = src_a;
    b = src_b;
    avl = LEN;

    start = read_csr(mcycle);

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vle32.v v0, (%0)" :: "r"(a));
        asm volatile ("vle32.v v8, (%0)" :: "r"(b));

#ifdef MUL_ADD
        /* len 4:       40 cycl */
        /* len 128:     40 cycl */
        /* len 256:     85 cycl */
        /* len 2048:    882 cycl */
        asm volatile ("vfmul.vf v16, v0, %0" :: "f"(scalar));
        asm volatile ("vfadd.vv v24, v16, v8");
        asm volatile ("vse32.v v24, (%0)" :: "r"(r));
#elif defined MUL_ADD_REUSE
        /* len 4:       40 cycl */
        /* len 128:     40 cycl */
        /* len 256:     88 cycl */
        /* len 2048:    1039 cycl */
        asm volatile ("vfmul.vf v0, v0, %0" :: "f"(scalar));
        asm volatile ("vfadd.vv v0, v0, v8");
        asm volatile ("vse32.v v0, (%0)" :: "r"(r));
#elif defined MACC
        /* len 4:       53 cycl */
        /* len 128:     53 cycl */
        /* len 256:     100 cycl */
        /* len 2048:    1051 cycl */
        asm volatile ("vfmacc.vf v8, %0, v0" :: "f"(alpha));
        asm volatile ("vse32.v v8, (%0)" :: "r"(r));
#endif

        a += vl;
        b += vl;
        r += vl;
    }

    end = read_csr(mcycle);

    check_result(LEN);
    printf("took %llu cycles\n", end - start);
}


int main()
{
    printf("################################ Testing vfmacc with %s %s and len %d #####################################\n", instr, loop, LEN);

    init_data();
    compute_expected();
#ifdef LOOP
    test_vfmacc_loop();
#else
    // test_vfmacc();
    test_vfmacc_v0();
    // test_vfmacc_pointers_on_l2();
#endif

    printf("############################################################################################\n");

    return 0;
}
