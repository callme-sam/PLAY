#include "internal/arch_interface.h"
#include "play.h"

#include <math.h>

#include "snrt.h"

static int linalg_cholesky_decomp_spatz_serial(const float *src, float *dst, const int dim)
{
    float ONE_f = 1.0f;
    float ZERO_f = 0.0f;

    size_t vl;
    size_t avl;
    size_t stride;
    size_t original_avl;

    float *row_m;
    float *row_n;
    float *ptr_dst;
    const float *ptr_src;

    float sum;
    float Lmm_inv;

    stride = dim * sizeof(float);

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
        Lmm_inv = ONE_f / dst[m * dim + m];

        for (int n = (m + 1); n < dim; n += vl) {
            ptr_src = src + (n * dim + m);
            ptr_dst = dst + (n * dim + m);
            avl = dim - n;

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
            asm volatile ("vfmv.v.f v0, %0" :: "f"(ZERO_f));

            for (int k = 0; k < m; k++) {
                row_m = dst + (m * dim + k);
                row_n = dst + (n * dim + k);

                asm volatile ("vlse32.v v16, (%0), %1" :: "r"(row_n), "r"(stride));
                snrt_cluster_hw_barrier();

                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_m));
            }

            asm volatile ("vlse32.v v8, (%0), %1" :: "r"(ptr_src), "r"(stride));
            snrt_cluster_hw_barrier();

            asm volatile ("vfsub.vv v8, v8, v0");
            asm volatile ("vfmul.vf v0, v8, %0" :: "f"(Lmm_inv));
            asm volatile ("vsse32.v v0, (%0), %1" :: "r"(ptr_dst), "r"(stride));
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
