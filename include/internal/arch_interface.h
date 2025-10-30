#ifndef ARCH_INTERFACE_H_
#define ARCH_INTERFACE_H_

int matrix_memcpy_impl(const float *src, float *dst, const int dim_M, const int dim_N);

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
