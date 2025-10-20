#include "utils.h"

#include <math.h>

#ifdef TARGET_IS_SPATZ
#include "snrt.h"
#include "printf.h"
#elif TARGET_IS_PULP_OPEN
#include "pmsis.h"
#endif  /* TARGET_IS_ */

void *my_alloc(const int bytes)
{
#ifdef TARGET_IS_SPATZ
    return snrt_l1alloc(bytes);
#elif TARGET_IS_PULP_OPEN
#ifdef  CLUSTER
    return pi_cl_l1_malloc((void *) 0, bytes);
#else   /* CLUSTER */
    return pi_fc_l1_malloc(bytes);
#endif  /* CLUTER */
#endif  /* TARGET_IS_ */
}

void barrier()
{
#ifdef TARGET_IS_SPATZ
    snrt_cluster_hw_barrier();
#elif TARGET_IS_PULP_OPEN
#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif  /* NUM_CORES */
#endif  /* TARGET_IS_ */
}

bool is_master_core()
{
#ifdef TARGET_IS_SPATZ
    return snrt_cluster_core_idx() == 0;
#elif TARGET_IS_PULP_OPEN
    return pi_core_id() == 0;
#endif  /* TARGET_IS_ */
}

bool scalar_compare(const float val_a, const float val_b)
{
    float abs_diff;

    abs_diff = fabs(val_a - val_b);
    if (abs_diff > TOLL)
        return false;

    return true;
}

bool vector_compare(const float *vec_a, const float *vec_b, const int len)
{
    float abs_diff;

    for (int i = 0; i < len; i++) {
        abs_diff = fabs(vec_a[i] - vec_b[i]);
        if (abs_diff > TOLL)
            return false;
    }

    return true;
}

bool vector_compare_abs(const float *vec_a, const float *vec_b, const int len)
{
    float abs_diff;

    for (int i = 0; i < len; i++) {
        abs_diff = fabs(fabs(vec_a[i]) - fabs(vec_b[i]));
        if (abs_diff > TOLL) {
            printf("abs_diff = %f\n", abs_diff);
            return false;
        }
    }

    return true;
}

bool matrix_compare(const float *mat_a, const float *mat_b, const int rows, const int cols)
{
    float abs_diff;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            abs_diff = fabs(mat_a[r * cols + c] - mat_b[r * cols + c]);
            if (abs_diff > TOLL)
                return false;
        }
    }

    return true;
}

bool matrix_compare_abs(const float *mat_a, const float *mat_b, const int rows, const int cols)
{
    float abs_diff;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            abs_diff = fabs(fabs(mat_a[r * cols + c]) - fabs(mat_b[r * cols + c]));
            if (abs_diff > TOLL) {
                printf("abs_diff = %f\n", abs_diff);
                return false;
            }
        }
    }

    return true;
}

#ifdef  PRINT_DATA

void scalar_print(const float val, const char *str)
{
    printf("Scalar %s\t= %.4f\n", str, val);
}

void vector_print(const float *vec, const int len, const char *str)
{
    printf("Vector %s\t= [ ", str);
    for (int i = 0; i < (len - 1); i++)
        printf("%.4f, ", vec[i]);
    printf("%.4f ]\n", vec[len - 1]);
}

void matrix_print(const float *mat, const int rows, const int cols, const char *str)
{
    printf("Matrix %s:\n", str);
    printf("[\n");
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < (cols - 1); c++)
            printf("%.4f,  ", mat[r * cols + c]);
        printf("%.4f;\n", mat[r * cols + (cols - 1)]);
    }
    printf("]\n");
}

#endif  /* PRINT_DATA */

#if TARGET_IS_SPATZ

unsigned long get_cycle()
{
    return read_csr(mcycle);
}

#endif  /* TARGET_IS_SPATZ */
