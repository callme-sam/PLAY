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
 * @brief Compares two floating-point values with a tollerance check
 *
 * @param[in] val_a First float value
 * @param[in] val_b Second float value
 *
 * @return true if all elements differ by less than TOLL
 * @return false if any element difference exceeds TOLL
 */
bool scalar_compare(const float val_a, const float val_b);

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
 * @brief Compares the absolute values of two floating-point vectors with a tolerance check
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
bool vector_compare_abs(const float *vec_a, const float *vec_b, const int len);

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
 * @brief Compares two floating-point matrices with a tollerance check
 *
 * @param[in] mat_a Pointer to the first matrix
 * @param[in] mat_b Pointer to the second matrix
 * @param[in] rows Number of rows for the two matrices
 * @param[in] cols Number of columts for the two matrices
 *
 *
 * @return true if all elements differ by less than TOLL
 * @return false if any alement difference exceeds TOLL
 */
bool matrix_compare(const float *mat_a, const float *mat_b, const int rows, const int cols);

/**
 * @brief Compares the absolute value of two floating-point matrices with a tollerance check
 *
 * @param[in] mat_a Pointer to the first matrix
 * @param[in] mat_b Pointer to the second matrix
 * @param[in] rows Number of rows for the two matrices
 * @param[in] cols Number of columts for the two matrices
 *
 *
 * @return true if all elements differ by less than TOLL
 * @return false if any alement difference exceeds TOLL
 */
bool matrix_compare_abs(const float *mat_a, const float *mat_b, const int rows, const int cols);

/**
 * @brief Printa a matrix to standard output
 *
 * @param[in] mat Pointer to the float matrix to print
 * @param[in] rows Number of rows of the matrix
 * @param[in] cols Number of cols of the matrix
 * @param[in] str Descriptive string to identify the matrix in output
 *
 * @note This function only produces output when PRINT_DATA macro is defined.
 * In other configurations, this function has no effect.
 */
void matrix_print(const float *mat, const int rows, const int cols, const char *str);

#endif  /* UTILS_H_ */
