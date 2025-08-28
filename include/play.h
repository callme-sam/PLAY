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
 * @brief Copies elements from a source vector to a destination vector.
 *
 * This function performs an element-by-element copy of floating-point values
 * from the source vector `src` to the destination vector `dst`.
 *
 * @param [in] src A pointer to the source vector.
 * @param [out] dst A pointer to the destination vector.
 * @param [in] len The number of elements to copy.
 *
 * @return int Returns 0 on success, non-zero on failure
 */
int vector_memcpy(const float *src, float *dst, const int len);

/**
 * @brief Fills a vector with a value.
 *
 * This function iterates through each element of a vector and sets it to the
 * specified constant value `val`.
 *
 * @param [out] vec A pointer to the destination vector to be modified.
 * @param [in] val The constant value to set each element to.
 * @param [in] len The number of elements in the vector.
 *
 * @return int Returns 0 on success, non-zero on failure
 */
int vector_set_all(float *vec, const float val, const int len);

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

/**
 * @brief Performs matrix transposition.
 *
 * This function computes the transpose of a matrix `src` and stores the result
 * in a destination matrix `dst`. The transpose operation swaps the rows and
 * columns of the source matrix.
 *
 * @param [in] src A pointer to the source matrix with dimensions dim_M x dim_N.
 * @param [out] dst A pointer to the destination matrix, which will have dimensions dim_N x dim_M.
 * @param [in] dim_M The number of rows in the source matrix.
 * @param [in] dim_N The number of columns in the source matrix.
 *
 * @return int Returns 0 on success.
 */
int matrix_trans(const float *src, float *dst, const int dim_M, const int dim_N);

/**
 * @brief Performs matrix multiplication with a transposed second matrix: dst = src_a * src_b^T.
 *
 * This function multiplies a matrix `src_a` by the transpose of a matrix `src_b`.
 * The result is stored in `dst`.
 *
 * @param [in] src_a A pointer to the first source matrix, with dimensions dim_M x dim_N.
 * @param [in] src_b A pointer to the second source matrix, with dimensions dim_P x dim_N.
 * @param [out] dst A pointer to the destination matrix, which will have dimensions dim_M x dim_P.
 * @param [in] dim_M The number of rows in the `src_a` and `dst` matrices.
 * @param [in] dim_N The number of columns in the `src_a` and `src_b` matrices.
 * @param [in] dim_P The number of rows in the `src_b` matrix and the number of columns in the `dst` matrix.
 *
 * @return int Returns 0 on success.
 */
int matrix_mul_trans(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P);

/**
 * @brief Copies elements from a source matrix to a destination matrix.
 *
 * This function performs an element-by-element copy of floating-point values
 * from the source matrix `src` to the destination matrix `dst`. The matrices
 * are treated as one-dimensional arrays in row-major order.
 *
 * @param [in] src A pointer to the source matrix.
 * @param [out] dst A pointer to the destination matrix.
 * @param [in] dim_M The number of rows in the matrices.
 * @param [in] dim_N The number of columns in the matrices.
 *
 * @return int Returns 0 on success, non-zero on error.
 */
int matrix_memcpy(const float *src, float *dst, const int dim_M, const int dim_N);

/**
 * @brief Fills a matrix with a constant value.
 *
 * This function iterates through each element of a matrix and sets it to the
 * specified constant value `val`. The matrix is treated as a one-dimensional
 * array in row-major order.
 *
 * @param [out] mat A pointer to the destination matrix to be modified.
 * @param [in] val The constant value to set each element to.
 * @param [in] dim_M The number of rows in the matrix.
 * @param [in] dim_N The number of columns in the matrix.
 *
 * @return int Returns 0 on success, non-zero on error
 */
int matrix_set_all(float *mat, const float val, const int dim_M, const int dim_N);

/**
 * @brief Swaps two rows of a matrix.
 *
 * This function swaps the contents of the specified rows, `row_a` and `row_b`,
 * within the matrix `mat`. The operation is performed in-place.
 *
 * @param [in,out] mat A pointer to the matrix where the rows will be swapped.
 * @param [in] row_a The index of the first row to be swapped (0-based).
 * @param [in] row_b The index of the second row to be swapped (0-based).
 * @param [in] dim_M The total number of rows in the matrix.
 * @param [in] dim_N The total number of columns in the matrix.
 *
 * @return int Returns 0 on success, non-zero on error.
 */
int matrix_swap_rows(float *mat, const int row_a, const int row_b, const int dim_M, const int dim_N);

#endif  /* PLAY_H_ */
