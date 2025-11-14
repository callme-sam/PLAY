#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static float ONE_f = 1.0f;
static float ZERO_f = 0.0f;
static float EPSILON = 1e-12;

int linalg_svd_lsv_pulp_open_spatz_serial(const float *src, float *mat_V, float *vec_S, float *dst, const int dim_M, const int dim_N)
{
    size_t original_avl;
    size_t stride;
    size_t avl;
    size_t vl;

    const float *p_src;
    float *p_dst;
    float *p_v;
    float *p_s;

    float sum;

    stride = dim_N * sizeof(float);

    for (int k = 0; k < dim_N; k++) {
        /* Optimization */
        if (vec_S[k] < EPSILON) {
            /* Set k-th column of dst to 0 */
            avl = dim_M;
            p_dst = dst;

            for (; avl > 0; avl -= vl) {
                asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
                asm volatile ("vfmv.v.f v0, %0" :: "f"(ZERO_f));
                asm volatile ("vsse32.v v0, (%0), %1" :: "r"(p_dst), "r"(stride));
                p_dst += vl * dim_N;
            }
        }

        for (int m = 0; m < dim_M; m++) {
            original_avl = dim_N;
            avl = dim_N;

            p_src = src + (m * dim_N);
            p_v = mat_V + k;

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
            asm volatile ("vfmv.v.f v16, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v24, %0" :: "f"(0.0f));

            for (; avl > 0; avl -= vl) {
                asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
                asm volatile ("vle32.v v0, (%0)" :: "r"(p_src));
                asm volatile ("vlse32.v v8, (%0), %1" :: "r"(p_v), "r"(stride));
                snrt_cluster_hw_barrier();
                asm volatile ("vfmacc.vv v16, v0, v8");
                snrt_cluster_hw_barrier();

                p_src += vl;
                p_v += vl * dim_N;
            }

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile ("vfredsum.vs v24, v16, v24");
            snrt_cluster_hw_barrier();

            asm volatile ("vfmv.f.s %0, v24" : "=f"(sum));
            dst[m * dim_N + k] = sum / vec_S[k];
            snrt_cluster_hw_barrier();
        }
    }

    return 0;
}


int linalg_svd_lsv_impl(const float *src, float *mat_V, float *vec_S, float *dst, const int dim_M, const int dim_N)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = linalg_svd_lsv_pulp_open_spatz_serial(src, mat_V, vec_S, dst, dim_M, dim_N);
#endif

    return ret;
}
