#include "utils.h"

#include <math.h>

#include "pmsis.h"

void barrier()
{
#ifdef CLUSTER
    pi_cl_team_barrier();
#endif
}

bool is_master_core()
{
    return pi_core_id() == 0;
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

void vector_print(const float *vec, const int len, const char *str)
{
#ifdef PRINT_DATA
    printf("Vector %s\t= [ ", str);
    for (int i = 0; i < (len - 1); i++)
        printf("%.4f, ", vec[i]);
    printf("%.4f ]\n", vec[len - 1]);
#endif  /* PRINT_DATA */
}