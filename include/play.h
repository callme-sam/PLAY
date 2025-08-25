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
 * @brief Performa element-wise subtraction of two vectors.
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
 * @brief Performa element-wise addition of two vectors.
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

#endif  /* PLAY_H_ */