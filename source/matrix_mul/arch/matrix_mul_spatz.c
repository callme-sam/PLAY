#include "internal/arch_interface.h"
#include "play.h"

#include "snrt.h"

static int matrix_mul_spatz_no_optimization(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t original_avl;
    size_t stride_b;
    size_t avl;
    size_t vl;

    const float *row_a;
    const float *col_b;

    float sum;

    original_avl = dim_N;
    stride_b = dim_P * sizeof(float);

    for (int m = 0; m < dim_M; m++) {
        for (int p = 0; p < dim_P; p++) {
            row_a = src_a + (m * dim_N);
            col_b = src_b + p;
            avl = dim_N;
            sum = 0;

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0));
            asm volatile ("vfmv.v.f v24, %0" :: "f"(0.0));

            for (; avl > 0; avl -= vl) {

                asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

                asm volatile ("vle32.v v8, (%0)" :: "r"(row_a));
                asm volatile ("vlse32.v v16, (%0), %1" :: "r"(col_b), "r"(stride_b));
                snrt_cluster_hw_barrier();

                asm volatile ("vfmacc.vv v0, v8, v16");

                row_a += vl;
                col_b += vl * dim_P;
            }

            asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(original_avl));
            asm volatile ("vfredusum.vs v24, v0, v24");
            asm volatile ("vfmv.f.s %0, v24" : "=f"(sum));

            dst[m * dim_P + p] = sum;
        }
    }

    return 0;
}

/* 21423 */
static int matrix_mul_spatz_serial_1xVL(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t avl;
    size_t vl;

    const float *elem_a;
    const float *row_b;
    float *row_dst;

    for (int p = 0; p < dim_P; p += vl) {
        avl = dim_P - p;
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r" (avl));

        for (int m = 0; m < dim_M; m++) {
            row_dst = dst + (m * dim_P + p);
            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

            for (int n = 0; n < dim_N; n++) {
                elem_a = src_a + (m * dim_N + n);
                row_b = src_b + (n * dim_P + p);

                asm volatile ("vle32.v v8, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v8" :: "f"(*elem_a));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst));
        }
    }

    return 0;
}

/* 20527 */
static int matrix_mul_spatz_serial_1xVL_unroll(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t avl;
    size_t vl;

    const float *elem_a1;
    const float *elem_a1_next;
    const float *row_b1;
    const float *row_b2;
    float *row_dst;

    for (int p = 0; p < dim_P; p += vl) {
        avl = dim_P - p;
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r" (avl));

        for (int m = 0; m < dim_M; m++) {
            row_dst = dst + (m * dim_P + p);
            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                elem_a1 = src_a + (m * dim_N + n);
                elem_a1_next = src_a + (m * dim_N + (n + 1));
                row_b1 = src_b + (n * dim_P + p);
                row_b2 = src_b + ((n + 1) * dim_P + p);

                asm volatile ("vle32.v v8, (%0)" :: "r"(row_b1));
                asm volatile ("vfmacc.vf v0, %0, v8" :: "f"(*elem_a1));

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b2));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*elem_a1_next));
            }

            if (dim_N % 2) {
                elem_a1 = src_a + (m * dim_N + (dim_N - 1));
                row_b1 = src_b + ((dim_N - 1) * dim_P + p);

                asm volatile ("vle32.v v8, (%0)" :: "r"(row_b1));
                asm volatile ("vfmacc.vf v0, %0, v8" :: "f"(*elem_a1));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst));
        }
    }

    return 0;
}

/* 19083 */
static int matrix_mul_spatz_serial_2xVL(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t avl;
    size_t vl;

    const float *elem_a1;
    const float *elem_a2;
    const float *row_b;
    float *row_dst1;
    float *row_dst2;

    for (int p = 0; p < dim_P; p += vl) {
        avl = dim_P - p;
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r" (avl));

        for (int m = 0; m < (dim_M - 1); m += 2) {
            row_dst1 = dst + (m * dim_P + p);
            row_dst2 = dst + ((m + 1) * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v8, %0" :: "f"(0.0f));

            for (int n = 0; n < dim_N; n++) {
                elem_a1 = src_a + (m * dim_N + n);
                elem_a2 = src_a + ((m + 1) * dim_N + n);
                row_b = src_b + (n * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*elem_a1));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*elem_a2));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
            asm volatile ("vse32.v v8, (%0)" :: "r"(row_dst2));
        }

        if (dim_M % 2) {
            row_dst1 = dst + ((dim_M - 1) * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

            for (int n = 0; n < dim_N; n++) {
                elem_a1 = src_a + ((dim_M - 1) * dim_N + n);
                row_b = src_b + (n * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*elem_a1));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
        }
    }

    return 0;
}

/* 18226 */
static int matrix_mul_spatz_serial_2xVL_unroll(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t avl;
    size_t vl;

    const float *row_a1;
    const float *row_a1_next;
    const float *row_a2;
    const float *row_a2_next;
    const float *row_b1;
    const float *row_b1_next;
    float *row_dst1;
    float *row_dst2;

    for (int p = 0; p < dim_P; p += vl) {
        avl = dim_P - p;
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r" (avl));

        for (int m = 0; m < (dim_M - 1); m += 2) {
            row_dst1 = dst + (m * dim_P + p);
            row_dst2 = dst + ((m + 1) * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v8, %0" :: "f"(0.0f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src_a + (m * dim_N + n);
                row_b1 = src_b + (n * dim_P + p);
                row_a2 = src_a + ((m + 1) * dim_N + n);

                row_a1_next = src_a + (m * dim_N + (n + 1));
                row_a2_next = src_a + ((m + 1) * dim_N + (n + 1));
                row_b1_next = src_b + ((n + 1) * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b1));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a2));

                asm volatile ("vle32.v v24, (%0)" :: "r"(row_b1_next));
                asm volatile ("vfmacc.vf v0, %0, v24" :: "f"(*row_a1_next));
                asm volatile ("vfmacc.vf v8, %0, v24" :: "f"(*row_a2_next));
            }

            if (dim_N % 2) {
                row_a1 = src_a + (m * dim_N + (dim_N - 1));
                row_b1 = src_b + ((dim_N - 1) * dim_P + p);
                row_a2 = src_a + ((m + 1) * dim_N + (dim_N - 1));

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b1));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a2));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
            asm volatile ("vse32.v v8, (%0)" :: "r"(row_dst2));
        }

        if (dim_M % 2) {
            row_dst1 = dst + ((dim_M - 1) * dim_P + p);
            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src_a + ((dim_M - 1) * dim_N + n);
                row_b1 = src_b + (n * dim_P + p);

                row_a1_next = src_a + ((dim_M - 1) * dim_N + (n + 1));
                row_b1_next = src_b + ((n + 1) * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b1));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));

                asm volatile ("vle32.v v24, (%0)" :: "r"(row_b1_next));
                asm volatile ("vfmacc.vf v0, %0, v24" :: "f"(*row_a1_next));
            }

            if (dim_N % 2) {
                row_a1 = src_a + ((dim_M - 1) * dim_N + (dim_N - 1));
                row_b1 = src_b + ((dim_N - 1) * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b1));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
        }
    }

    return 0;
}

/* 18233 */
static int matrix_mul_spatz_serial_3xVL(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t avl;
    size_t vl;

    const float *row_a1;
    const float *row_a2;
    const float *row_a3;
    const float *row_b;
    float *row_dst1;
    float *row_dst2;
    float *row_dst3;

    for (int p = 0; p < dim_P; p += vl) {
        avl = dim_P - p;
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        for (int m = 0; m < (dim_M - 2); m += 3) {
            row_dst1 = dst + (m * dim_P + p);
            row_dst2 = dst + ((m + 1) * dim_P + p);
            row_dst3 = dst + ((m + 2) * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v8, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v16, %0" :: "f"(0.0f));

            for (int n = 0; n < dim_N; n++) {
                row_a1 = src_a + (m * dim_N + n);
                row_a2 = src_a + ((m + 1) * dim_N + n);
                row_a3 = src_a + ((m + 2) * dim_N + n);
                row_b = src_b + (n * dim_P + p);

                asm volatile ("vle32.v v24, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v24" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v8, %0, v24" :: "f"(*row_a2));
                asm volatile ("vfmacc.vf v16, %0, v24" :: "f"(*row_a3));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
            asm volatile ("vse32.v v8, (%0)" :: "r"(row_dst2));
            asm volatile ("vse32.v v16, (%0)" :: "r"(row_dst3));
        }

        for (int m = (dim_M - (dim_M % 3)); m < dim_M; m++) {
            row_dst1 = dst + (m * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

            for (int n = 0; n < dim_N; n++) {
                row_a1 = src_a + (m * dim_N + n);
                row_b = src_b + (n * dim_P + p);

                asm volatile ("vle32.v v24, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v24" :: "f"(*row_a1));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
        }
    }

    return 0;
}

/* 18291 */
static int matrix_mul_spatz_serial_3xVL_unroll(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t avl;
    size_t vl;

    const float *row_a1, *row_a1_next;
    const float *row_a2, *row_a2_next;
    const float *row_a3, *row_a3_next;
    const float *row_b, *row_b_next;
    float *row_dst1;
    float *row_dst2;
    float *row_dst3;

    for (int p = 0; p < dim_P; p += vl) {
        avl = dim_P - p;
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        for (int m = 0; m < (dim_M - 2); m += 3) {
            row_dst1 = dst + (m * dim_P + p);
            row_dst2 = dst + ((m + 1) * dim_P + p);
            row_dst3 = dst + ((m + 2) * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v8, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v16, %0" :: "f"(0.0f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src_a + (m * dim_N + n);
                row_a2 = src_a + ((m + 1) * dim_N + n);
                row_a3 = src_a + ((m + 2) * dim_N + n);

                row_a1_next = src_a + (m * dim_N + (n + 1));
                row_a2_next = src_a + ((m + 1) * dim_N + (n + 1));
                row_a3_next = src_a + ((m + 2) * dim_N + (n + 1));

                row_b = src_b + (n * dim_P + p);
                row_b_next = src_b + ((n + 1) * dim_P + p);

                asm volatile ("vle32.v v24, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v24" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v8, %0, v24" :: "f"(*row_a2));
                asm volatile ("vfmacc.vf v16, %0, v24" :: "f"(*row_a3));

                asm volatile ("vle32.v v24, (%0)" :: "r"(row_b_next));
                asm volatile ("vfmacc.vf v0, %0, v24" :: "f"(*row_a1_next));
                asm volatile ("vfmacc.vf v8, %0, v24" :: "f"(*row_a2_next));
                asm volatile ("vfmacc.vf v16, %0, v24" :: "f"(*row_a3_next));
            }

            if (dim_N % 2) {
                row_a1 = src_a + (m * dim_N + (dim_N - 1));
                row_a2 = src_a + ((m + 1) * dim_N + (dim_N - 1));
                row_a3 = src_a + ((m + 2) * dim_N + (dim_N - 1));

                row_b = src_b + ((dim_N - 1) * dim_P + p);

                asm volatile ("vle32.v v24, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v24" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v8, %0, v24" :: "f"(*row_a2));
                asm volatile ("vfmacc.vf v16, %0, v24" :: "f"(*row_a3));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
            asm volatile ("vse32.v v8, (%0)" :: "r"(row_dst2));
            asm volatile ("vse32.v v16, (%0)" :: "r"(row_dst3));
        }

        for (int m = (dim_M - (dim_M % 3)); m < dim_M; m++) {
            row_dst1 = dst + (m * dim_P + p);
            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src_a + (m * dim_N + n);
                row_a1_next = src_a + (m * dim_N + (n + 1));
                row_b = src_b + (n * dim_P + p);
                row_b_next = src_b + ((n + 1) * dim_P + p);

                asm volatile ("vle32.v v24, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v24" :: "f"(*row_a1));

                asm volatile ("vle32.v v24, (%0)" :: "r"(row_b_next));
                asm volatile ("vfmacc.vf v0, %0, v24" :: "f"(*row_a1_next));
            }

            if (dim_N % 2) {
                row_a1 = src_a + (m * dim_N + (dim_N - 1));
                row_b = src_b + ((dim_N - 1) * dim_P + p);

                asm volatile ("vle32.v v24, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v24" :: "f"(*row_a1));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
        }
    }

    return 0;
}

/* 19083 */
static int matrix_mul_spatz_serial_4xVL(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t avl;
    size_t vl;

    const float *row_a1;
    const float *row_a2;
    const float *row_a3;
    const float *row_a4;
    const float *row_b;
    float *row_dst1;
    float *row_dst2;
    float *row_dst3;
    float *row_dst4;

    for (int p = 0; p < dim_P; p += vl) {
        avl = dim_P - p;
        asm volatile ("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl));

        for (int m = 0; m < (dim_M - 3); m += 4) {
            row_dst1 = dst + (m * dim_P + p);
            row_dst2 = dst + ((m + 1) * dim_P + p);
            row_dst3 = dst + ((m + 2) * dim_P + p);
            row_dst4 = dst + ((m + 3) * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v4, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v8, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v12, %0" :: "f"(0.0f));

            for (int n = 0; n < dim_N; n++) {
                row_a1 = src_a + (m * dim_N + n);
                row_a2 = src_a + ((m + 1) * dim_N + n);
                row_a3 = src_a + ((m + 2) * dim_N + n);
                row_a4 = src_a + ((m + 3) * dim_N + n);
                row_b = src_b + (n * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v4, %0, v16" :: "f"(*row_a2));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a3));
                asm volatile ("vfmacc.vf v12, %0, v16" :: "f"(*row_a4));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
            asm volatile ("vse32.v v4, (%0)" :: "r"(row_dst2));
            asm volatile ("vse32.v v8, (%0)" :: "r"(row_dst3));
            asm volatile ("vse32.v v12, (%0)" :: "r"(row_dst4));
        }

        for (int m = (dim_M - (dim_M % 4)); m < dim_M; m++) {
            row_dst1 = dst + (m * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

            for (int n = 0; n < dim_N; n++) {
                row_a1 = src_a + (m * dim_N + n);
                row_b = src_b + (n * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
        }
    }

    return 0;
}

/* 18566 */
static int matrix_mul_spatz_serial_4xVL_unroll(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t avl;
    size_t vl;

    const float *row_a1;
    const float *row_a2;
    const float *row_a3;
    const float *row_a4;
    const float *row_a1_next;
    const float *row_a2_next;
    const float *row_a3_next;
    const float *row_a4_next;
    const float *row_b;
    const float *row_b_next;
    float *row_dst1;
    float *row_dst2;
    float *row_dst3;
    float *row_dst4;

    for (int p = 0; p < dim_P; p += vl) {
        avl = dim_P - p;
        asm volatile ("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(vl) : "r"(avl));

        for (int m = 0; m < (dim_M - 3); m += 4) {
            row_dst1 = dst + (m * dim_P + p);
            row_dst2 = dst + ((m + 1) * dim_P + p);
            row_dst3 = dst + ((m + 2) * dim_P + p);
            row_dst4 = dst + ((m + 3) * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v4, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v8, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v12, %0" :: "f"(0.0f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src_a + (m * dim_N + n);
                row_a2 = src_a + ((m + 1) * dim_N + n);
                row_a3 = src_a + ((m + 2) * dim_N + n);
                row_a4 = src_a + ((m + 3) * dim_N + n);

                row_a1_next = src_a + (m * dim_N + (n + 1));
                row_a2_next = src_a + ((m + 1) * dim_N + (n + 1));
                row_a3_next = src_a + ((m + 2) * dim_N + (n + 1));
                row_a4_next = src_a + ((m + 3) * dim_N + (n + 1));

                row_b = src_b + (n * dim_P + p);
                row_b_next = src_b + ((n + 1) * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v4, %0, v16" :: "f"(*row_a2));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a3));
                asm volatile ("vfmacc.vf v12, %0, v16" :: "f"(*row_a4));

                asm volatile ("vle32.v v20, (%0)" :: "r"(row_b_next));
                asm volatile ("vfmacc.vf v0, %0, v20" :: "f"(*row_a1_next));
                asm volatile ("vfmacc.vf v4, %0, v20" :: "f"(*row_a2_next));
                asm volatile ("vfmacc.vf v8, %0, v20" :: "f"(*row_a3_next));
                asm volatile ("vfmacc.vf v12, %0, v20" :: "f"(*row_a4_next));
            }

            if (dim_N % 2) {
                row_b = src_b + ((dim_N - 1) * dim_P + p);
                row_a1 = src_a + (m * dim_N + (dim_N - 1));
                row_a2 = src_a + ((m + 1) * dim_N + (dim_N - 1));
                row_a3 = src_a + ((m + 2) * dim_N + (dim_N - 1));
                row_a4 = src_a + ((m + 3) * dim_N + (dim_N - 1));

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v4, %0, v16" :: "f"(*row_a2));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a3));
                asm volatile ("vfmacc.vf v12, %0, v16" :: "f"(*row_a4));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
            asm volatile ("vse32.v v4, (%0)" :: "r"(row_dst2));
            asm volatile ("vse32.v v8, (%0)" :: "r"(row_dst3));
            asm volatile ("vse32.v v12, (%0)" :: "r"(row_dst4));
        }

        for (int m = (dim_M - (dim_M % 4)); m < dim_M; m++) {
            row_dst1 = dst + (m * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src_a + (m * dim_N + n);
                row_a1_next = src_a + (m * dim_N + (n + 1));
                row_b = src_b + (n * dim_P + p);
                row_b_next = src_b + ((n + 1) * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));

                asm volatile ("vle32.v v20, (%0)" :: "r"(row_b_next));
                asm volatile ("vfmacc.vf v0, %0, v20" :: "f"(*row_a1_next));
            }

            if (dim_N % 2) {
                row_b = src_b + ((dim_N - 1) * dim_P + p);
                row_a1 = src_a + (m * dim_N + (dim_N - 1));

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
        }
    }

    return 0;
}

/* 21703 */
static int matrix_mul_spatz_serial_8xVL(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t avl;
    size_t vl;

    const float *row_a1;
    const float *row_a2;
    const float *row_a3;
    const float *row_a4;
    const float *row_a5;
    const float *row_a6;
    const float *row_a7;
    const float *row_a8;
    const float *row_b;
    float *row_dst1;
    float *row_dst2;
    float *row_dst3;
    float *row_dst4;
    float *row_dst5;
    float *row_dst6;
    float *row_dst7;
    float *row_dst8;

    for (int p = 0; p < dim_P; p += vl) {
        avl = dim_P - p;
        asm volatile ("vsetvli %0, %1, e32, m2, ta, ma" : "=r"(vl) : "r"(avl));

        for (int m = 0; m < (dim_M - 7); m += 8) {
            row_dst1 = dst + (m * dim_P + p);
            row_dst2 = dst + ((m + 1) * dim_P + p);
            row_dst3 = dst + ((m + 2) * dim_P + p);
            row_dst4 = dst + ((m + 3) * dim_P + p);
            row_dst5 = dst + ((m + 4) * dim_P + p);
            row_dst6 = dst + ((m + 5) * dim_P + p);
            row_dst7 = dst + ((m + 6) * dim_P + p);
            row_dst8 = dst + ((m + 7) * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v2, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v4, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v6, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v8, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v10, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v12, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v14, %0" :: "f"(0.0f));

            for (int n = 0; n < dim_N; n++) {
                row_a1 = src_a + (m * dim_N + n);
                row_a2 = src_a + ((m + 1) * dim_N + n);
                row_a3 = src_a + ((m + 2) * dim_N + n);
                row_a4 = src_a + ((m + 3) * dim_N + n);
                row_a5 = src_a + ((m + 4) * dim_N + n);
                row_a6 = src_a + ((m + 5) * dim_N + n);
                row_a7 = src_a + ((m + 6) * dim_N + n);
                row_a8 = src_a + ((m + 7) * dim_N + n);
                row_b = src_b + (n * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v2, %0, v16" :: "f"(*row_a2));
                asm volatile ("vfmacc.vf v4, %0, v16" :: "f"(*row_a3));
                asm volatile ("vfmacc.vf v6, %0, v16" :: "f"(*row_a4));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a5));
                asm volatile ("vfmacc.vf v10, %0, v16" :: "f"(*row_a6));
                asm volatile ("vfmacc.vf v12, %0, v16" :: "f"(*row_a7));
                asm volatile ("vfmacc.vf v14, %0, v16" :: "f"(*row_a8));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
            asm volatile ("vse32.v v2, (%0)" :: "r"(row_dst2));
            asm volatile ("vse32.v v4, (%0)" :: "r"(row_dst3));
            asm volatile ("vse32.v v6, (%0)" :: "r"(row_dst4));
            asm volatile ("vse32.v v8, (%0)" :: "r"(row_dst5));
            asm volatile ("vse32.v v10, (%0)" :: "r"(row_dst6));
            asm volatile ("vse32.v v12, (%0)" :: "r"(row_dst7));
            asm volatile ("vse32.v v14, (%0)" :: "r"(row_dst8));
        }

        for (int m = (dim_M - (dim_M % 8)); m < dim_M; m++) {
            row_dst1 = dst + (m * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

            for (int n = 0; n < dim_N; n++) {
                row_a1 = src_a + (m * dim_N + n);
                row_b = src_b + (n * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
        }
    }

    return 0;
}

/* 22727 */
static int matrix_mul_spatz_serial_8xVL_unroll(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t avl;
    size_t vl;

    const float *row_a1;
    const float *row_a2;
    const float *row_a3;
    const float *row_a4;
    const float *row_a5;
    const float *row_a6;
    const float *row_a7;
    const float *row_a8;
    const float *row_a1_next;
    const float *row_a2_next;
    const float *row_a3_next;
    const float *row_a4_next;
    const float *row_a5_next;
    const float *row_a6_next;
    const float *row_a7_next;
    const float *row_a8_next;
    const float *row_b;
    const float *row_b_next;
    float *row_dst1;
    float *row_dst2;
    float *row_dst3;
    float *row_dst4;
    float *row_dst5;
    float *row_dst6;
    float *row_dst7;
    float *row_dst8;

    for (int p = 0; p < dim_P; p += vl) {
        avl = dim_P - p;
        asm volatile ("vsetvli %0, %1, e32, m2, ta, ma" : "=r"(vl) : "r"(avl));

        for (int m = 0; m < (dim_M - 7); m += 8) {
            row_dst1 = dst + (m * dim_P + p);
            row_dst2 = dst + ((m + 1) * dim_P + p);
            row_dst3 = dst + ((m + 2) * dim_P + p);
            row_dst4 = dst + ((m + 3) * dim_P + p);
            row_dst5 = dst + ((m + 4) * dim_P + p);
            row_dst6 = dst + ((m + 5) * dim_P + p);
            row_dst7 = dst + ((m + 6) * dim_P + p);
            row_dst8 = dst + ((m + 7) * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v2, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v4, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v6, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v8, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v10, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v12, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v14, %0" :: "f"(0.0f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src_a + (m * dim_N + n);
                row_a2 = src_a + ((m + 1) * dim_N + n);
                row_a3 = src_a + ((m + 2) * dim_N + n);
                row_a4 = src_a + ((m + 3) * dim_N + n);
                row_a5 = src_a + ((m + 4) * dim_N + n);
                row_a6 = src_a + ((m + 5) * dim_N + n);
                row_a7 = src_a + ((m + 6) * dim_N + n);
                row_a8 = src_a + ((m + 7) * dim_N + n);

                row_a1_next = src_a + (m * dim_N + (n + 1));
                row_a2_next = src_a + ((m + 1) * dim_N + (n + 1));
                row_a3_next = src_a + ((m + 2) * dim_N + (n + 1));
                row_a4_next = src_a + ((m + 3) * dim_N + (n + 1));
                row_a5_next = src_a + ((m + 4) * dim_N + (n + 1));
                row_a6_next = src_a + ((m + 5) * dim_N + (n + 1));
                row_a7_next = src_a + ((m + 6) * dim_N + (n + 1));
                row_a8_next = src_a + ((m + 7) * dim_N + (n + 1));

                row_b = src_b + (n * dim_P + p);
                row_b_next = src_b + ((n + 1) * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v2, %0, v16" :: "f"(*row_a2));
                asm volatile ("vfmacc.vf v4, %0, v16" :: "f"(*row_a3));
                asm volatile ("vfmacc.vf v6, %0, v16" :: "f"(*row_a4));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a5));
                asm volatile ("vfmacc.vf v10, %0, v16" :: "f"(*row_a6));
                asm volatile ("vfmacc.vf v12, %0, v16" :: "f"(*row_a7));
                asm volatile ("vfmacc.vf v14, %0, v16" :: "f"(*row_a8));

                asm volatile ("vle32.v v18, (%0)" :: "r"(row_b_next));
                asm volatile ("vfmacc.vf v0, %0, v18" :: "f"(*row_a1_next));
                asm volatile ("vfmacc.vf v2, %0, v18" :: "f"(*row_a2_next));
                asm volatile ("vfmacc.vf v4, %0, v18" :: "f"(*row_a3_next));
                asm volatile ("vfmacc.vf v6, %0, v18" :: "f"(*row_a4_next));
                asm volatile ("vfmacc.vf v8, %0, v18" :: "f"(*row_a5_next));
                asm volatile ("vfmacc.vf v10, %0, v18" :: "f"(*row_a6_next));
                asm volatile ("vfmacc.vf v12, %0, v18" :: "f"(*row_a7_next));
                asm volatile ("vfmacc.vf v14, %0, v18" :: "f"(*row_a8_next));
            }

            if (dim_N % 2) {
                row_a1 = src_a + (m * dim_N + (dim_N - 1));
                row_a2 = src_a + ((m + 1) * dim_N + (dim_N - 1));
                row_a3 = src_a + ((m + 2) * dim_N + (dim_N - 1));
                row_a4 = src_a + ((m + 3) * dim_N + (dim_N - 1));
                row_a5 = src_a + ((m + 4) * dim_N + (dim_N - 1));
                row_a6 = src_a + ((m + 5) * dim_N + (dim_N - 1));
                row_a7 = src_a + ((m + 6) * dim_N + (dim_N - 1));
                row_a8 = src_a + ((m + 7) * dim_N + (dim_N - 1));
                row_b = src_b + ((dim_N - 1) * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v2, %0, v16" :: "f"(*row_a2));
                asm volatile ("vfmacc.vf v4, %0, v16" :: "f"(*row_a3));
                asm volatile ("vfmacc.vf v6, %0, v16" :: "f"(*row_a4));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a5));
                asm volatile ("vfmacc.vf v10, %0, v16" :: "f"(*row_a6));
                asm volatile ("vfmacc.vf v12, %0, v16" :: "f"(*row_a7));
                asm volatile ("vfmacc.vf v14, %0, v16" :: "f"(*row_a8));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
            asm volatile ("vse32.v v2, (%0)" :: "r"(row_dst2));
            asm volatile ("vse32.v v4, (%0)" :: "r"(row_dst3));
            asm volatile ("vse32.v v6, (%0)" :: "r"(row_dst4));
            asm volatile ("vse32.v v8, (%0)" :: "r"(row_dst5));
            asm volatile ("vse32.v v10, (%0)" :: "r"(row_dst6));
            asm volatile ("vse32.v v12, (%0)" :: "r"(row_dst7));
            asm volatile ("vse32.v v14, (%0)" :: "r"(row_dst8));
        }

        for (int m = (dim_M - (dim_M % 8)); m < dim_M ; m++) {
            row_dst1 = dst + (m * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src_a + (m * dim_N + n);
                row_a1_next = src_a + (m * dim_N + (n + 1));
                row_b = src_b + (n * dim_P + p);
                row_b_next = src_b + ((n + 1) * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));

                asm volatile ("vle32.v v18, (%0)" :: "r"(row_b_next));
                asm volatile ("vfmacc.vf v0, %0, v18" :: "f"(*row_a1_next));
            }

            if (dim_N % 2) {
                row_a1 = src_a + (m * dim_N + (dim_N - 1));
                row_b = src_b + ((dim_N - 1) * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
        }
    }

    return 0;
}

/* 41550 */
static int matrix_mul_spatz_serial_16xVL(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t avl;
    size_t vl;

    const float *row_a1;
    const float *row_a2;
    const float *row_a3;
    const float *row_a4;
    const float *row_a5;
    const float *row_a6;
    const float *row_a7;
    const float *row_a8;
    const float *row_a9;
    const float *row_a10;
    const float *row_a11;
    const float *row_a12;
    const float *row_a13;
    const float *row_a14;
    const float *row_a15;
    const float *row_a16;
    const float *row_b;
    float *row_dst1;
    float *row_dst2;
    float *row_dst3;
    float *row_dst4;
    float *row_dst5;
    float *row_dst6;
    float *row_dst7;
    float *row_dst8;
    float *row_dst9;
    float *row_dst10;
    float *row_dst11;
    float *row_dst12;
    float *row_dst13;
    float *row_dst14;
    float *row_dst15;
    float *row_dst16;

    for (int p = 0; p < dim_P; p += vl) {
        avl = dim_P - p;
        asm volatile ("vsetvli %0, %1, e32, m1, ta, ma" : "=r"(vl) : "r"(avl));

        for (int m = 0; m < (dim_M - 15); m += 16) {
            row_dst1 = dst + (m * dim_P + p);
            row_dst2 = dst + ((m + 1) * dim_P + p);
            row_dst3 = dst + ((m + 2) * dim_P + p);
            row_dst4 = dst + ((m + 3) * dim_P + p);
            row_dst5 = dst + ((m + 4) * dim_P + p);
            row_dst6 = dst + ((m + 5) * dim_P + p);
            row_dst7 = dst + ((m + 6) * dim_P + p);
            row_dst8 = dst + ((m + 7) * dim_P + p);
            row_dst9 = dst + ((m + 8) * dim_P + p);
            row_dst10 = dst + ((m + 9) * dim_P + p);
            row_dst11 = dst + ((m + 10) * dim_P + p);
            row_dst12 = dst + ((m + 11) * dim_P + p);
            row_dst13 = dst + ((m + 12) * dim_P + p);
            row_dst14 = dst + ((m + 13) * dim_P + p);
            row_dst15 = dst + ((m + 14) * dim_P + p);
            row_dst16 = dst + ((m + 15) * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v1, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v2, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v3, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v4, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v5, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v6, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v7, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v8, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v9, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v10, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v11, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v12, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v13, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v14, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v15, %0" :: "f"(0.0f));

            for (int n = 0; n < dim_N; n++) {
                row_a1 = src_a + (m * dim_N + n);
                row_a2 = src_a + ((m + 1) * dim_N + n);
                row_a3 = src_a + ((m + 2) * dim_N + n);
                row_a4 = src_a + ((m + 3) * dim_N + n);
                row_a5 = src_a + ((m + 4) * dim_N + n);
                row_a6 = src_a + ((m + 5) * dim_N + n);
                row_a7 = src_a + ((m + 6) * dim_N + n);
                row_a8 = src_a + ((m + 7) * dim_N + n);
                row_a9 = src_a + ((m + 8) * dim_N + n);
                row_a10 = src_a + ((m + 9) * dim_N + n);
                row_a11 = src_a + ((m + 10) * dim_N + n);
                row_a12 = src_a + ((m + 11) * dim_N + n);
                row_a13 = src_a + ((m + 12) * dim_N + n);
                row_a14 = src_a + ((m + 13) * dim_N + n);
                row_a15 = src_a + ((m + 14) * dim_N + n);
                row_a16 = src_a + ((m + 15) * dim_N + n);
                row_b = src_b + (n * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v1, %0, v16" :: "f"(*row_a2));
                asm volatile ("vfmacc.vf v2, %0, v16" :: "f"(*row_a3));
                asm volatile ("vfmacc.vf v3, %0, v16" :: "f"(*row_a4));
                asm volatile ("vfmacc.vf v4, %0, v16" :: "f"(*row_a5));
                asm volatile ("vfmacc.vf v5, %0, v16" :: "f"(*row_a6));
                asm volatile ("vfmacc.vf v6, %0, v16" :: "f"(*row_a7));
                asm volatile ("vfmacc.vf v7, %0, v16" :: "f"(*row_a8));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a9));
                asm volatile ("vfmacc.vf v9, %0, v16" :: "f"(*row_a10));
                asm volatile ("vfmacc.vf v10, %0, v16" :: "f"(*row_a11));
                asm volatile ("vfmacc.vf v11, %0, v16" :: "f"(*row_a12));
                asm volatile ("vfmacc.vf v12, %0, v16" :: "f"(*row_a13));
                asm volatile ("vfmacc.vf v13, %0, v16" :: "f"(*row_a14));
                asm volatile ("vfmacc.vf v14, %0, v16" :: "f"(*row_a15));
                asm volatile ("vfmacc.vf v15, %0, v16" :: "f"(*row_a16));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
            asm volatile ("vse32.v v1, (%0)" :: "r"(row_dst2));
            asm volatile ("vse32.v v2, (%0)" :: "r"(row_dst3));
            asm volatile ("vse32.v v3, (%0)" :: "r"(row_dst4));
            asm volatile ("vse32.v v4, (%0)" :: "r"(row_dst5));
            asm volatile ("vse32.v v5, (%0)" :: "r"(row_dst6));
            asm volatile ("vse32.v v6, (%0)" :: "r"(row_dst7));
            asm volatile ("vse32.v v7, (%0)" :: "r"(row_dst8));
            asm volatile ("vse32.v v8, (%0)" :: "r"(row_dst9));
            asm volatile ("vse32.v v9, (%0)" :: "r"(row_dst10));
            asm volatile ("vse32.v v10, (%0)" :: "r"(row_dst11));
            asm volatile ("vse32.v v11, (%0)" :: "r"(row_dst12));
            asm volatile ("vse32.v v12, (%0)" :: "r"(row_dst13));
            asm volatile ("vse32.v v13, (%0)" :: "r"(row_dst14));
            asm volatile ("vse32.v v14, (%0)" :: "r"(row_dst15));
            asm volatile ("vse32.v v15, (%0)" :: "r"(row_dst16));
        }

        for (int m = (dim_M - (dim_M % 16)); m < dim_M; m++) {
            row_dst1 = dst + (m * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

            for (int n = 0; n < dim_N; n++) {
                row_a1 = src_a + (m * dim_N + n);
                row_b = src_b + (n * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
        }
    }

    return 0;
}

/* 43244 */
static int matrix_mul_spatz_serial_16xVL_unroll(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    size_t avl;
    size_t vl;

    const float *row_a1, *row_a1_next;
    const float *row_a2, *row_a2_next;
    const float *row_a3, *row_a3_next;
    const float *row_a4, *row_a4_next;
    const float *row_a5, *row_a5_next;
    const float *row_a6, *row_a6_next;
    const float *row_a7, *row_a7_next;
    const float *row_a8, *row_a8_next;
    const float *row_a9, *row_a9_next;
    const float *row_a10, *row_a10_next;
    const float *row_a11, *row_a11_next;
    const float *row_a12, *row_a12_next;
    const float *row_a13, *row_a13_next;
    const float *row_a14, *row_a14_next;
    const float *row_a15, *row_a15_next;
    const float *row_a16, *row_a16_next;
    const float *row_b, *row_b_next;
    float *row_dst1;
    float *row_dst2;
    float *row_dst3;
    float *row_dst4;
    float *row_dst5;
    float *row_dst6;
    float *row_dst7;
    float *row_dst8;
    float *row_dst9;
    float *row_dst10;
    float *row_dst11;
    float *row_dst12;
    float *row_dst13;
    float *row_dst14;
    float *row_dst15;
    float *row_dst16;

    for (int p = 0; p < dim_P; p += vl) {
        avl = dim_P - p;
        asm volatile ("vsetvli %0, %1, e32, m1, ta, ma" : "=r"(vl) : "r"(avl));

        for (int m = 0; m < (dim_M - 15); m += 16) {
            row_dst1 = dst + (m * dim_P + p);
            row_dst2 = dst + ((m + 1) * dim_P + p);
            row_dst3 = dst + ((m + 2) * dim_P + p);
            row_dst4 = dst + ((m + 3) * dim_P + p);
            row_dst5 = dst + ((m + 4) * dim_P + p);
            row_dst6 = dst + ((m + 5) * dim_P + p);
            row_dst7 = dst + ((m + 6) * dim_P + p);
            row_dst8 = dst + ((m + 7) * dim_P + p);
            row_dst9 = dst + ((m + 8) * dim_P + p);
            row_dst10 = dst + ((m + 9) * dim_P + p);
            row_dst11 = dst + ((m + 10) * dim_P + p);
            row_dst12 = dst + ((m + 11) * dim_P + p);
            row_dst13 = dst + ((m + 12) * dim_P + p);
            row_dst14 = dst + ((m + 13) * dim_P + p);
            row_dst15 = dst + ((m + 14) * dim_P + p);
            row_dst16 = dst + ((m + 15) * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v1, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v2, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v3, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v4, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v5, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v6, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v7, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v8, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v9, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v10, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v11, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v12, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v13, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v14, %0" :: "f"(0.0f));
            asm volatile ("vfmv.v.f v15, %0" :: "f"(0.0f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src_a + (m * dim_N + n);
                row_a2 = src_a + ((m + 1) * dim_N + n);
                row_a3 = src_a + ((m + 2) * dim_N + n);
                row_a4 = src_a + ((m + 3) * dim_N + n);
                row_a5 = src_a + ((m + 4) * dim_N + n);
                row_a6 = src_a + ((m + 5) * dim_N + n);
                row_a7 = src_a + ((m + 6) * dim_N + n);
                row_a8 = src_a + ((m + 7) * dim_N + n);
                row_a9 = src_a + ((m + 8) * dim_N + n);
                row_a10 = src_a + ((m + 9) * dim_N + n);
                row_a11 = src_a + ((m + 10) * dim_N + n);
                row_a12 = src_a + ((m + 11) * dim_N + n);
                row_a13 = src_a + ((m + 12) * dim_N + n);
                row_a14 = src_a + ((m + 13) * dim_N + n);
                row_a15 = src_a + ((m + 14) * dim_N + n);
                row_a16 = src_a + ((m + 15) * dim_N + n);

                row_a1_next = src_a + (m * dim_N + (n + 1));
                row_a2_next = src_a + ((m + 1) * dim_N + (n + 1));
                row_a3_next = src_a + ((m + 2) * dim_N + (n + 1));
                row_a4_next = src_a + ((m + 3) * dim_N + (n + 1));
                row_a5_next = src_a + ((m + 4) * dim_N + (n + 1));
                row_a6_next = src_a + ((m + 5) * dim_N + (n + 1));
                row_a7_next = src_a + ((m + 6) * dim_N + (n + 1));
                row_a8_next = src_a + ((m + 7) * dim_N + (n + 1));
                row_a9_next = src_a + ((m + 8) * dim_N + (n + 1));
                row_a10_next = src_a + ((m + 9) * dim_N + (n + 1));
                row_a11_next = src_a + ((m + 10) * dim_N +(n + 1));
                row_a12_next = src_a + ((m + 11) * dim_N +(n + 1));
                row_a13_next = src_a + ((m + 12) * dim_N +(n + 1));
                row_a14_next = src_a + ((m + 13) * dim_N +(n + 1));
                row_a15_next = src_a + ((m + 14) * dim_N +(n + 1));
                row_a16_next = src_a + ((m + 15) * dim_N +(n + 1));

                row_b = src_b + (n * dim_P + p);
                row_b_next = src_b + ((n + 1) * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v1, %0, v16" :: "f"(*row_a2));
                asm volatile ("vfmacc.vf v2, %0, v16" :: "f"(*row_a3));
                asm volatile ("vfmacc.vf v3, %0, v16" :: "f"(*row_a4));
                asm volatile ("vfmacc.vf v4, %0, v16" :: "f"(*row_a5));
                asm volatile ("vfmacc.vf v5, %0, v16" :: "f"(*row_a6));
                asm volatile ("vfmacc.vf v6, %0, v16" :: "f"(*row_a7));
                asm volatile ("vfmacc.vf v7, %0, v16" :: "f"(*row_a8));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a9));
                asm volatile ("vfmacc.vf v9, %0, v16" :: "f"(*row_a10));
                asm volatile ("vfmacc.vf v10, %0, v16" :: "f"(*row_a11));
                asm volatile ("vfmacc.vf v11, %0, v16" :: "f"(*row_a12));
                asm volatile ("vfmacc.vf v12, %0, v16" :: "f"(*row_a13));
                asm volatile ("vfmacc.vf v13, %0, v16" :: "f"(*row_a14));
                asm volatile ("vfmacc.vf v14, %0, v16" :: "f"(*row_a15));
                asm volatile ("vfmacc.vf v15, %0, v16" :: "f"(*row_a16));

                asm volatile ("vle32.v v17, (%0)" :: "r"(row_b_next));
                asm volatile ("vfmacc.vf v0, %0, v17" :: "f"(*row_a1_next));
                asm volatile ("vfmacc.vf v1, %0, v17" :: "f"(*row_a2_next));
                asm volatile ("vfmacc.vf v2, %0, v17" :: "f"(*row_a3_next));
                asm volatile ("vfmacc.vf v3, %0, v17" :: "f"(*row_a4_next));
                asm volatile ("vfmacc.vf v4, %0, v17" :: "f"(*row_a5_next));
                asm volatile ("vfmacc.vf v5, %0, v17" :: "f"(*row_a6_next));
                asm volatile ("vfmacc.vf v6, %0, v17" :: "f"(*row_a7_next));
                asm volatile ("vfmacc.vf v7, %0, v17" :: "f"(*row_a8_next));
                asm volatile ("vfmacc.vf v8, %0, v17" :: "f"(*row_a9_next));
                asm volatile ("vfmacc.vf v9, %0, v17" :: "f"(*row_a10_next));
                asm volatile ("vfmacc.vf v10, %0, v17" :: "f"(*row_a11_next));
                asm volatile ("vfmacc.vf v11, %0, v17" :: "f"(*row_a12_next));
                asm volatile ("vfmacc.vf v12, %0, v17" :: "f"(*row_a13_next));
                asm volatile ("vfmacc.vf v13, %0, v17" :: "f"(*row_a14_next));
                asm volatile ("vfmacc.vf v14, %0, v17" :: "f"(*row_a15_next));
                asm volatile ("vfmacc.vf v15, %0, v17" :: "f"(*row_a16_next));
            }

            if (dim_N % 2) {
                row_a1 = src_a + (m * dim_N + (dim_N - 1));
                row_a2 = src_a + ((m + 1) * dim_N + (dim_N - 1));
                row_a3 = src_a + ((m + 2) * dim_N + (dim_N - 1));
                row_a4 = src_a + ((m + 3) * dim_N + (dim_N - 1));
                row_a5 = src_a + ((m + 4) * dim_N + (dim_N - 1));
                row_a6 = src_a + ((m + 5) * dim_N + (dim_N - 1));
                row_a7 = src_a + ((m + 6) * dim_N + (dim_N - 1));
                row_a8 = src_a + ((m + 7) * dim_N + (dim_N - 1));
                row_a9 = src_a + ((m + 8) * dim_N + (dim_N - 1));
                row_a10 = src_a + ((m + 9) * dim_N + (dim_N - 1));
                row_a11 = src_a + ((m + 10) * dim_N + (dim_N - 1));
                row_a12 = src_a + ((m + 11) * dim_N + (dim_N - 1));
                row_a13 = src_a + ((m + 12) * dim_N + (dim_N - 1));
                row_a14 = src_a + ((m + 13) * dim_N + (dim_N - 1));
                row_a15 = src_a + ((m + 14) * dim_N + (dim_N - 1));
                row_a16 = src_a + ((m + 15) * dim_N + (dim_N - 1));
                row_b = src_b + ((dim_N - 1) * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
                asm volatile ("vfmacc.vf v1, %0, v16" :: "f"(*row_a2));
                asm volatile ("vfmacc.vf v2, %0, v16" :: "f"(*row_a3));
                asm volatile ("vfmacc.vf v3, %0, v16" :: "f"(*row_a4));
                asm volatile ("vfmacc.vf v4, %0, v16" :: "f"(*row_a5));
                asm volatile ("vfmacc.vf v5, %0, v16" :: "f"(*row_a6));
                asm volatile ("vfmacc.vf v6, %0, v16" :: "f"(*row_a7));
                asm volatile ("vfmacc.vf v7, %0, v16" :: "f"(*row_a8));
                asm volatile ("vfmacc.vf v8, %0, v16" :: "f"(*row_a9));
                asm volatile ("vfmacc.vf v9, %0, v16" :: "f"(*row_a10));
                asm volatile ("vfmacc.vf v10, %0, v16" :: "f"(*row_a11));
                asm volatile ("vfmacc.vf v11, %0, v16" :: "f"(*row_a12));
                asm volatile ("vfmacc.vf v12, %0, v16" :: "f"(*row_a13));
                asm volatile ("vfmacc.vf v13, %0, v16" :: "f"(*row_a14));
                asm volatile ("vfmacc.vf v14, %0, v16" :: "f"(*row_a15));
                asm volatile ("vfmacc.vf v15, %0, v16" :: "f"(*row_a16));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
            asm volatile ("vse32.v v1, (%0)" :: "r"(row_dst2));
            asm volatile ("vse32.v v2, (%0)" :: "r"(row_dst3));
            asm volatile ("vse32.v v3, (%0)" :: "r"(row_dst4));
            asm volatile ("vse32.v v4, (%0)" :: "r"(row_dst5));
            asm volatile ("vse32.v v5, (%0)" :: "r"(row_dst6));
            asm volatile ("vse32.v v6, (%0)" :: "r"(row_dst7));
            asm volatile ("vse32.v v7, (%0)" :: "r"(row_dst8));
            asm volatile ("vse32.v v8, (%0)" :: "r"(row_dst9));
            asm volatile ("vse32.v v9, (%0)" :: "r"(row_dst10));
            asm volatile ("vse32.v v10, (%0)" :: "r"(row_dst11));
            asm volatile ("vse32.v v11, (%0)" :: "r"(row_dst12));
            asm volatile ("vse32.v v12, (%0)" :: "r"(row_dst13));
            asm volatile ("vse32.v v13, (%0)" :: "r"(row_dst14));
            asm volatile ("vse32.v v14, (%0)" :: "r"(row_dst15));
            asm volatile ("vse32.v v15, (%0)" :: "r"(row_dst16));
        }

        for (int m = (dim_M - (dim_M % 16)); m < dim_M; m++) {
            row_dst1 = dst + (m * dim_P + p);

            asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0f));

            for (int n = 0; n < (dim_N - 1); n += 2) {
                row_a1 = src_a + (m * dim_N + n);
                row_a1_next = src_a + (m * dim_N + (n + 1));
                row_b = src_b + (n * dim_P + p);
                row_b_next = src_b + ((n + 1) * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));

                asm volatile ("vle32.v v17, (%0)" :: "r"(row_b_next));
                asm volatile ("vfmacc.vf v0, %0, v17" :: "f"(*row_a1_next));
            }

            if (dim_N % 2) {
                row_a1 = src_a + (m * dim_N + (dim_N - 1));
                row_b = src_b + ((dim_N - 1) * dim_P + p);

                asm volatile ("vle32.v v16, (%0)" :: "r"(row_b));
                asm volatile ("vfmacc.vf v0, %0, v16" :: "f"(*row_a1));
            }

            asm volatile ("vse32.v v0, (%0)" :: "r"(row_dst1));
        }
    }

    return 0;
}


int matrix_mul_impl(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P)
{
    int ret;

#if NUM_CC > 1
    #error "Parallel execution on SPATZ not implemented yet"
#else
    ret = matrix_mul_spatz_serial_2xVL_unroll(src_a, src_b, dst, dim_M, dim_N, dim_P);
#endif

    return ret;
}
