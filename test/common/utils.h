#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>

#define TOLL 0.004f

/**
 * @brief Synchronizes all cores in the cluster using a barrier
 *
 * @note This function only has effect when CLUSTER macro is defined.
 * In non-cluster configurations, this function does nothing.
 */
void barrier();

/**
 * @brief Checks if the current core is the master core, i.e. core ID 0
 *
 * @return true if the current core is the master core (core ID 0)
 * @return false if the current core is not the master core
 */
bool is_master_core();

/**
 * @brief Compares two floating-point vectors with a tolerance check
 *
 * @param[in] vec_a Pointer to the first float vector
 * @param[in] vec_b Pointer to the second float vector
 * @param[in] len Length of the vectors to compare
 *
 * @return true if all elements differ by less than TOLL
 * @return false if any element difference exceeds TOLL
 *
 * @warning Both vectors must have at least 'len' elements allocated
 */
bool vector_compare(const float *vec_a, const float *vec_b, const int len);

/**
 * @brief Prints a vector to standard output
 *
 * @param[in] vec Pointer to the float vector to print
 * @param[in] len Length of the vector
 * @param[in] str Descriptive string to identify the vector in output
 *
 * @note This function only produces output when PRINT_DATA macro is defined.
 * In other configurations, this function has no effect.
 */
void vector_print(const float *vec, const int len, const char *str);

/**
 * @brief Prints a scalar float value to standard output
 *
 * @param[in] val The float scalar to print
 * @param[in] str Descriptive string to identify the scalar in output
 *
 * @note This function only produces output when PRINT_DATA macro is defined.
 * In other configurations, this function has no effect.
 */
void scalar_print(const float val, const char *str);

#endif  /* UTILS_H_ */