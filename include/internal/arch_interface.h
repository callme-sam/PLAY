#ifndef ARCH_INTERFACE_H_
#define ARCH_INTERFACE_H_

int linalg_cholesky_decomp_impl(const float *src, float *dst, const int dim);
int linalg_gemv_impl(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N);
int linalg_gemv_trans_impl(const float *mat, const float *vec_x, const float *vec_y, const float alpha, const float beta, float *dst, const int dim_M, const int dim_N);
int linalg_lu_decomp_impl(float *mat, int *perm, const int dim_M, const int dim_N);
int linalg_lu_solve_impl(const float *mat, const float *vec, const int *perm, float *result, const int dim_M, const int dim_N);
int linalg_svd_impl(const float *src, float *dst, float *mat_V, float *vec_S, const int dim_M, const int dim_N);
int linalg_svd_jacobi_impl(float *mat, float *mat_V, float *vec_S, const int dim_M);
int linalg_svd_lsv_impl(const float *src, float *mat_V, float *vec_S, float *dst, const int dim_M, const int dim_N);

int matrix_memcpy_impl(const float *src, float *dst, const int dim_M, const int dim_N);
int matrix_mul_impl(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P);
int matrix_mul_trans_A_impl(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P);
int matrix_mul_trans_B_impl(const float *src_a, const float *src_b, float *dst, const int dim_M, const int dim_N, const int dim_P);
int matrix_set_all_impl(float *mat, const float val, const int dim_M, const int dim_N);
int matrix_swap_rows_impl(float *mat, const int row_a, const int row_b, const int dim_N);
int matrix_trans_impl(const float *src, float *dst, const int dim_M, const int dim_N);

int vector_add_impl(const float *src_a, const float *src_b, float *dst, const int len);
int vector_axpy_impl(const float *src_a, const float *src_b, const float alpha, float *dst, const int len);
int vector_dot_impl(const float *src_a, const float *src_b, float *dst, const int len);
int vector_memcpy_impl(const float *src, float *dst, const int len);
int vector_min_impl(const float *src, float *min, const int len);
int vector_mul_impl(const float *src_a, const float *src_b, float *dst, const int len);
int vector_offset_impl(const float *src, const float offset, float *dst, const int len);
int vector_scale_impl(const float *src, const float val, float *dst, const int len);
int vector_set_all_impl(float *vec, const float val, const int len);
int vector_sub_impl(const float *src_a, const float *src_b, float *dst, const int len);

#endif /* ARCH_INTERFACE_H_*/
