#ifndef ARCH_INTERFACE_H_
#define ARCH_INTERFACE_H_

int vector_mul_pulp_open(const float *src_a, const float *src_b, float *dst, const int len);
int vector_mul_spatz(const float *src_a, const float *src_b, float *dst, const int len);

#endif  /* ARCH_INTERFACE_H_ */
