#include "internal/arch_interface.h"
#include "play.h"

#include <math.h>

#include "snrt.h"

static const float ONE_f = 1.0f;
static const float ZERO_f = 0.0f;

static int linalg_cholesky_decomp_spatz_serial(const float *src, float *dst, const int dim)
{
    size_t original_avl;
    size_t avl;
    size_t vl;

    float *row_m;
    float *row_n;
    float sum;

    for (int m = 0; m < dim; m++) {
        row_m = dst + (m * dim);
        original_avl = m;
        avl = m;
        sum = 0;

        if (m != 0) {
            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
            asm volatile ("vfmv.v.f v0, %0" :: "f"(ZERO_f));
            asm volatile ("vfmv.v.f v8, %0" :: "f"(ZERO_f));

            for (; avl > 0; avl -= vl) {
                asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_m));

                asm volatile ("vfmacc.vv v0, v16, v16");

                row_m += vl;
            }

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile ("vfredsum.vs v8, v0, v8");

            asm volatile ("vfmv.f.s %0, v8" : "=f"(sum));
        }

        dst[m * dim + m] = sqrtf(src[m * dim + m] - sum);

        for (int n = (m + 1); n < dim; n++) {
            row_m = dst + (m * dim);
            row_n = dst + (n * dim);
            avl = m;
            sum = 0;

            if (m != 0) {
                asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
                asm volatile ("vfmv.v.f v0, %0" :: "f"(ZERO_f));
                asm volatile ("vfmv.v.f v8, %0" :: "f"(ZERO_f));

                for (; avl > 0; avl -= vl) {
                    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

                    asm volatile ("vle32.v v16, (%0)" :: "r"(row_m));
                    asm volatile ("vle32.v v24, (%0)" :: "r"(row_n));

                    asm volatile ("vfmacc.vv v0, v16, v24");

                    row_m += vl;
                    row_n += vl;
                }

                asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(original_avl));
                asm volatile ("vfredsum.vs v8, v0, v8");

                asm volatile ("vfmv.f.s %0, v8" : "=f"(sum));
            }

            dst[n * dim + m] = (ONE_f / dst[m * dim + m]) * (src[n * dim + m] - sum);
            snrt_cluster_hw_barrier();
        }
    }

    return 0;
}

int linalg_cholesky_decomp_impl(const float *src, float *dst, const int dim)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = linalg_cholesky_decomp_spatz_serial(src, dst, dim);
#endif

    return ret;
}
