#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

#if 1

/* 711 */
static int matrix_memcpy_spatz_serial(const float *src, float *dst, const int dim_M, const int dim_N)
{
    size_t avl;
    size_t vl;

    const float *p_src;
    float *p_dst;

    avl = dim_M * dim_N;
    p_src = src;
    p_dst = dst;

    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        asm volatile ("vle32.v v0, (%0)" :: "r"(p_src));

        asm volatile ("vmv.v.v v8, v0");

        asm volatile ("vse32.v v8, (%0)" :: "r"(p_dst));

        p_src += vl;
        p_dst += vl;
    }

    return 0;
}
#else

/* 350 */
static int matrix_memcpy_spatz_serial(const float *src, float *dst, const int dim_M, const int dim_N)
{
    snrt_dma_txid_t dma_id;

    dma_id = snrt_dma_start_1d(dst, src, dim_M * dim_N * sizeof(float));
    snrt_dma_wait(dma_id);

    return 0;
}

#endif

int matrix_memcpy_impl(const float *src, float *dst, const int dim_M, const int dim_N)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = matrix_memcpy_spatz_serial(src, dst, dim_M, dim_N);
#endif

    return ret;
}
