#ifndef PLAY_H_
#define PLAY_H_

/**
 * @brief Performs element-wise multiplication of two vectors.
 *
 * This function computes the element-wise product of two floating-point vectors (`src_a` and `src_b`)
 * and stores the result in the `dst` vector. The execution mode (cluster or fabric controller)
 * is determined by the `CLUSTER` macro. If `CLUSTER` is defined, a parallel version of the
 * function is used; otherwise, a serial version is executed.
 *
 * @param [in] src_a A pointer to the first source float vector.
 * @param [in] src_b A pointer to the second source float vector.
 * @param [out] dst A pointer to the destination vector where the results will be stored.
 * @param [in] len The length of the vectors. All three vectors are assumed to have the same length.
 *
 * @return int Returns 0 on success, or a non-zero value on failure.
 */
int vector_mul(const float *src_a, const float *src_b, float *dst, const int len);

/**
 * @brief Performs element-wise subtraction of two vectors.
 *
 * This function computes the element-wise subtraction of two floating-point vectors(`src_a` and `src_b`)
 * and stores the result in the `dst` vector. The execution mode (cluster or fabric controller)
 * is determined by the `CLUSTER` macro. If `CLUSTER` is defined, a parallel version of the
 * function is used; otherwise, a serial version is executed.
 *
 * @param [in] src_a A pointer to the first source float vector.
 * @param [in] src_b A pointer to the second source float vector.
 * @param [out] dst A pointer to the destination vector where the results will be stored.
 * @param [in] len The length of the vectors. All three vectors are assumed to have the same length.
 *
 * @return int Returns 0 on success, or a non-zero value on failure.
 */
int vector_sub(const float *src_a, const float *src_b, float *dst, const int len);

/**
 * @brief Performs element-wise addition of two vectors.
 *
 * This function computes the element-wise addition of two floating-point vectors(`src_a` and `src_b`)
 * and stores the result in the `dst` vector. The execution mode (cluster or fabric controller)
 * is determined by the `CLUSTER` macro. If `CLUSTER` is defined, a parallel version of the
 * function is used; otherwise, a serial version is executed.
 *
 * @param [in] src_a A pointer to the first source float vector.
 * @param [in] src_b A pointer to the second source float vector.
 * @param [out] dst A pointer to the destination vector where the results will be stored.
 * @param [in] len The length of the vectors. All three vectors are assumed to have the same length.
 *
 * @return int Returns 0 on success, or a non-zero value on failure.
 */
int vector_add(const float *src_a, const float *src_b, float *dst, const int len);

/**
 * @brief Adds a scalar offset to each element of a vector.
 *
 * This function performs an element-wise addition of a constant scalar value (`offset`)
 * to a source vector (`src`) and stores the result in a destination vector (`dst`).
 * The execution mode (cluster or fabric controller) is determined by the `CLUSTER` macro. If `CLUSTER`
 * is defined, a parallel version of the function is used; otherwise, a serial version is executed.
 *
 * @param [in] src A pointer to the source vector.
 * @param [in] offset The scalar value to add to each element of the vector.
 * @param [out] dst A pointer to the destination vector where the results will be stored.
 * @param [in] len The length of the vectors.
 *
 * @return int Returns 0 on success, or a non-zero value on failure.
 */
int vector_offset(const float *src, const float offset, float *dst, const int len);

/**
 * @brief Performs element-wise scaling of a vector.
 *
 * This function multiplies each element of a source vector (`src`) by a constant
 * scalar value (`val`) and stores the result in a destination vector (`dst`).
 * The execution mode (cluster or fabric controller) is determined by the `CLUSTER` macro. If `CLUSTER`
 * is defined, a parallel version of the function is used; otherwise, a serial version is executed.
 *
 * @param [in] src A pointer to the source vector.
 * @param [in] val The scalar value to multiply each element by.
 * @param [out] dst A pointer to the destination vector where the results will be stored.
 * @param [in] len The length of the vectors.
 *
 * @return int Returns 0 on success, or a non-zero value on failure.
 */
int vector_scale(const float *src, const float val, float *dst, const int len);

/**
 * @brief Finds the minimum value in a vector.
 *
 * This function iterates through a vector of floating-point numbers (`src`) to find
 * and return its minimum value.
 * The execution mode (cluster or fabric controller) is determined by the `CLUSTER` macro. If `CLUSTER`
 * is defined, a parallel version of the function is used; otherwise, a serial version is executed.
 *
 * @param [in] src A pointer to the source vector.
 * @param [out] min A pointer to the memory location where the minimum value will be stored.
 * @param [in] len The length of the vector.
 *
 * @return int Returns 0 on success, or a non-zero value on failure.
 */
int vector_min(const float *src, float *min, const int len);

/**
 * @brief Computes the dot product of two vectors.
 *
 * This function calculates the dot product of two vectors, `src_a` and `src_b`, by
 * summing the products of their corresponding elements. The result is
 * a single scalar value which is stored in the memory location pointed to by `dst`.
 * The execution mode (cluster or fabric controller) is determined by the `CLUSTER` macro. If `CLUSTER`
 * is defined, a parallel version of the function is used; otherwise, a serial version is executed.
 *
 *
 * @param [in] src_a A pointer to the first source vector.
 * @param [in] src_b A pointer to the second source vector.
 * @param [out] dst A pointer to the memory location where the scalar result will be stored.
 * @param [in] len The length of the vectors.
 *
 * @return int Returns 0 on success, non-zero on failure.
 */
int vector_dot(const float *src_a, const float *src_b, float *dst, const int len);

/**
 * @brief Computes the AXPY operation: dst = α·src_a + src_b.
 *
 * This function performs an element-wise multiplication of the source vector `src_a` by
 * a scalar `alpha`, and then adds the corresponding elements of the vector `src_b`.
 * The result is stored in a separate destination vector `dst`. The original source
 * vectors `src_a` and `src_b` are not modified.
 *
 * @param [in] src_a A pointer to the first source vector.
 * @param [in] src_b A pointer to the second source vector.
 * @param [in] alpha The scalar value (α) to multiply with each element of `src_a`.
 * @param [out] dst A pointer to the destination vector where the final result is stored.
 * @param [in] len The length of the vectors.
 *
 * @return int Returns 0 on success, non-zero on failure.
 */
int vector_axpy(const float *src_a, const float *src_b, const float alpha, float *dst, const int len);

/**
 * @brief Performs matrix multiplication: dst = src_a * src_b.
 *
 * This function multiplies the matrix `src_a` by the matrix `src_b` and stores the
 * resulting matrix in `dst`. This operation is valid only if the number of columns
 * of `src_a` is equal to the number of rows of `src_b`.
 *
 * @param [in] src_a A pointer to the first source matrix, with dimensions dim_M x dim_N.
 * @param [in] src_b A pointer to the second source matrix, with dimensions dim_N x dim_P.
 * @param [out] dst A pointer to the destination matrix, with dimensions dim_M x dim_P.
 * @param [in] dim_M The number of rows in the `src_a` and `dst` matrices.
 * @param [in] dim_N The number of columns in the `src_a` matrix and the number of rows in the `src_b` matrix.
 * @param [in] dim_P The number of columns in the `src_b` and `dst` matrices.
 *
 * @return int Returns 0 on success.
 */
int matrix_mul(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P);

#endif  /* PLAY_H_ */
