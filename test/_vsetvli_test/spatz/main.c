#include "snrt.h"
#include "printf.h"

#include <math.h>
#include <stdbool.h>

#define LEN 2048

#if MUL == 1
    #define VL_MUL "m1"
    size_t EXP_VL = 16;
#elif MUL == 2
    #define VL_MUL "m2"
    size_t EXP_VL = 32;
#elif MUL == 4
    #define VL_MUL "m4"
    size_t EXP_VL = 64;
#elif MUL == 8
    #define VL_MUL "m8"
    size_t EXP_VL = 128;
#else
#error "Invalid MUL value, must be 1,2,4,8"
#endif


static void test_vsetvli()
{
    size_t avl;
    size_t vl;

    avl = LEN;

    asm volatile ("vsetvli %0, %1, e32," VL_MUL ", ta, ma" : "=r"(vl) : "r"(avl));

#if MUL == 8
    asm volatile ("vfadd.vv v0, v8, v16");
    asm volatile ("vfadd.vv v0, v8, v16");
#elif MUL == 4
    asm volatile ("vfadd.vv v0, v8, v16");
    asm volatile ("vfadd.vv v0, v8, v16");
    asm volatile ("vfadd.vv v0, v8, v16");
    asm volatile ("vfadd.vv v0, v8, v16");
#elif MUL == 2
    asm volatile ("vfadd.vv v0, v8, v16");
    asm volatile ("vfadd.vv v0, v8, v16");
    asm volatile ("vfadd.vv v0, v8, v16");
    asm volatile ("vfadd.vv v0, v8, v16");
    asm volatile ("vfadd.vv v0, v8, v16");
    asm volatile ("vfadd.vv v0, v8, v16");
    asm volatile ("vfadd.vv v0, v8, v16");
    asm volatile ("vfadd.vv v0, v8, v16");
    asm volatile ("vfadd.vv v0, v8, v16");
    asm volatile ("vfadd.vv v0, v8, v16");
#endif


    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32," VL_MUL ", ta, ma" : "=r"(vl) : "r"(avl));

        if (vl != EXP_VL)
            printf("Error at iter. vl:%u - expected vl with %s: %u\n", vl, VL_MUL, EXP_VL);
    }
}


static void test_vsetvli_basic()
{
    size_t avl;
    size_t vl;

    avl = LEN;

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

    asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0));
    asm volatile ("vfmv.v.f v8, %0" :: "f"(0.0));

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        printf("vl=%u\n", vl);
    }
}


int main()
{
    printf("######################################## vsetvli TEST w\\ %s ###############################################\n\n", VL_MUL);

    // test_vsetvli();
    test_vsetvli_basic();

    printf("\n##########################################################################################################\n\n");

    return 0;
}
