#include <stdint.h>

#include "snrt.h"
#include "printf.h"

#define NITER 100
#define REPEAT 5
#define LEN 256

float val_a = 10;
float val_b = 5;
float val_c;

#if defined(EW8)
    typedef uint8_t  VTYPE;
    #define ELEM_BITS 8
    #define VSET "e8"
#elif defined(EW16)
    typedef uint16_t VTYPE;
    #define ELEM_BITS 16
    #define VSET "e16"
#elif defined(EW32)
    typedef float    VTYPE;
    #define ELEM_BITS 32
    #define VSET "e32"
#elif defined(EW64)
    typedef double   VTYPE;
    #define ELEM_BITS 64
    #define VSET "e64"
#else
    #error "Define one of EW8, EW16, EW32, EW64"
#endif

VTYPE *a __attribute__((aligned(32)));
VTYPE *b __attribute__((aligned(32)));
VTYPE *c __attribute__((aligned(32)));

static void init_vectors()
{
    a = snrt_l1alloc(LEN * sizeof(VTYPE));
    b = snrt_l1alloc(LEN * sizeof(VTYPE));
    c = snrt_l1alloc(LEN * sizeof(VTYPE));

    for (int i = 0; i < LEN; i++) {
        a[i] = (VTYPE)val_a;
        b[i] = (VTYPE)val_b;
        c[i] = 0;
    }

    val_c = val_a / val_b;
}

static float test_latency_fdiv_vv()
{
    unsigned long start;
    unsigned long end;
    size_t avl;
    size_t vl;
    float lat;

    avl = LEN;
    start = 0;
    end = 0;

    asm volatile ("vsetvli %0, %1, " VSET ", m1, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vl" VSET ".v v1, (%0)" :: "r"(a));
    asm volatile ("vl" VSET ".v v2, (%0)" :: "r"(b));

    snrt_cluster_hw_barrier();
    start = read_csr(mcycle);

    for (int i = 0; i < NITER; i++) {
        asm volatile ("vfdiv.vv v1, v1, v2");
        asm volatile ("vfdiv.vv v1, v1, v2");
        asm volatile ("vfdiv.vv v1, v1, v2");
        asm volatile ("vfdiv.vv v1, v1, v2");
    }

    end = read_csr(mcycle);
    snrt_cluster_hw_barrier();

    lat = (float)(end - start) / (float)(4 * NITER);
    return lat;
}

static float test_throughput_fdiv_vv()
{
    unsigned long start;
    unsigned long end;
    size_t avl;
    size_t vl;
    float thr;

    avl = LEN;
    start = 0;
    end = 0;

    asm volatile ("vsetvli %0, %1, " VSET ", m1, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vl" VSET ".v v1, (%0)" :: "r"(a));
    asm volatile ("vl" VSET ".v v2, (%0)" :: "r"(b));
    asm volatile ("vl" VSET ".v v3, (%0)" :: "r"(a));
    asm volatile ("vl" VSET ".v v4, (%0)" :: "r"(b));
    asm volatile ("vl" VSET ".v v5, (%0)" :: "r"(a));
    asm volatile ("vl" VSET ".v v6, (%0)" :: "r"(b));
    asm volatile ("vl" VSET ".v v7, (%0)" :: "r"(a));
    asm volatile ("vl" VSET ".v v8, (%0)" :: "r"(b));

    snrt_cluster_hw_barrier();
    start = read_csr(mcycle);

    for (int i = 0; i < NITER; i++) {
        asm volatile ("vfdiv.vv v10, v1, v2");
        asm volatile ("vfdiv.vv v11, v3, v4");
        asm volatile ("vfdiv.vv v12, v5, v6");
        asm volatile ("vfdiv.vv v13, v7, v8");
    }

    end = read_csr(mcycle);
    snrt_cluster_hw_barrier();

    thr = (float)(end - start) / (float)(4 * NITER);
    return thr;
}

int main()
{
    printf("################################### Testing fdiv using %s ##################################\n", VSET);

    float lat = 0;
    float thr = 0;

    init_vectors();

    for (int i = 0; i < REPEAT; i++) {
        lat += test_latency_fdiv_vv();
        thr += test_throughput_fdiv_vv();
    }

    printf("Latency       : %f cycles/inst\n", lat/REPEAT);
    printf("Throughput    : %f cycles/inst\n", thr/REPEAT);

    printf("############################################################################################\n");

  return 0;
}
