#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int linalg_gemv_spatz_serial(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N)
{
    if (alpha == 0.0f) {
        if (beta == 0.0f)
            vector_set_all(dst, 0.0, dim_M);
        else if (beta == 1.0f)
            vector_memcpy(vec_y, dst, dim_M);
        else
            vector_scale(vec_y, beta, dst, dim_M);
        return 0;
    }

    size_t row_avl_orig;
    size_t row_avl;
    size_t col_avl;
    size_t vl;
    float sum;

    const float *p_row_mat;
    const float *p_vec_x;
    const float *p_vec_y;
    const float *p_dst;

    for (int m = 0; m < dim_M; m++) {
        p_row_mat = mat + (m * dim_N);
        p_vec_x = vec_x;

        row_avl_orig = dim_N;
        row_avl = dim_N;

        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(row_avl));
        asm volatile ("vfmv.v.f v16, %0" :: "f"(0.0f));
        asm volatile ("vfmv.v.f v24, %0" :: "f"(0.0f));
        snrt_cluster_hw_barrier();

        for(; row_avl > 0; row_avl -= vl) {
            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(row_avl));

            asm volatile ("vle32.v v0, (%0)" :: "r"(p_row_mat));
            asm volatile ("vle32.v v8, (%0)" :: "r"(p_vec_x));

            asm volatile ("vfmacc.vv v16, v0, v8");
            snrt_cluster_hw_barrier();

            p_row_mat += vl;
            p_vec_x += vl;
        }

        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(row_avl_orig));
        asm volatile ("vfredsum.vs v24, v16, v24");
        snrt_cluster_hw_barrier();

        asm volatile ("vfmv.f.s %0, v24" : "=f"(sum));
        snrt_cluster_hw_barrier();
        dst[m] = sum * alpha;
    }

    p_dst = dst;
    p_vec_y = vec_y;
    col_avl = dim_M;

    for (; col_avl > 0; col_avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(col_avl));

        asm volatile ("vle32.v v0, (%0)" :: "r"(p_vec_y));
        asm volatile ("vle32.v v8, (%0)" :: "r"(p_dst));

        asm volatile("vfmul.vf v16, v0, %0" :: "f"(beta));
        asm volatile ("vfadd.vv v24, v16, v8");

        asm volatile ("vse32.v v24, (%0)" :: "r"(p_dst));

        p_dst += vl;
        p_vec_y += vl;
    }

    return 0;
}

#if 0
static int linalg_gemv_spatz_serial_v2(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N)
{
    if (alpha == 0.0f) {
        if (beta == 0.0f)
            vector_set_all(dst, 0.0, dim_M);
        else if (beta == 1.0f)
            vector_memcpy(vec_y, dst, dim_M);
        else
            vector_scale(vec_y, beta, dst, dim_M);
        return 0;
    }

    size_t row_avl_orig;
    size_t row_avl;
    size_t col_avl;
    size_t vl;
    float sum;

    const float *p_row_mat;
    const float *p_vec_x;


    for (int m = 0; m < dim_M; m++) {
        p_row_mat = mat + (m * dim_N);
        p_vec_x = vec_x;

        row_avl_orig = dim_N;
        row_avl = dim_N;

        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(row_avl));
        asm volatile ("vfmv.v.f v16, %0" :: "f"(0.0f));
        asm volatile ("vfmv.v.f v24, %0" :: "f"(0.0f));
        snrt_cluster_hw_barrier();

        for(; row_avl > 0; row_avl -= vl) {
            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(row_avl));

            asm volatile ("vle32.v v0, (%0)" :: "r"(p_row_mat));
            asm volatile ("vle32.v v8, (%0)" :: "r"(p_vec_x));

            asm volatile ("vfmacc.vv v16, v0, v8");
            snrt_cluster_hw_barrier();

            p_row_mat += vl;
            p_vec_x += vl;
        }

        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(row_avl_orig));
        asm volatile ("vfredsum.vs v24, v16, v24");
        snrt_cluster_hw_barrier();

        asm volatile ("vfmv.f.s %0, v24" : "=f"(sum));
        snrt_cluster_hw_barrier();

        dst[m] = (sum * alpha) + (vec_y[m] * beta);
    }

    return 0;
}
#endif

int linalg_gemv_impl(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not supported yet"
#else
    ret = linalg_gemv_spatz_serial(mat, vec_x, vec_y, alpha, beta, dst, dim_M, dim_N);
#endif

    return ret;
}
