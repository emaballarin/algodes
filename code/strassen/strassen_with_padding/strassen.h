#ifndef __STRASSEN__

void strassen_matrix_multiplication(float** C, float const* const* const A, float const* const* const B, size_t n);
void strassen_matrix_multiplication_odd(float** C, float const* const* const A, float const* const* const B, size_t n);
void strassen_matrix_multiplication_rect(float** C, const float* const* const A, const float* const* const B,
                                         size_t Arow, size_t Acol, size_t Bcol);
void strassen_matrix_multiplication_rect_memc(float** C, const float* const* const A, const float* const* const B,
                                              size_t Arow, size_t Acol, size_t Bcol);
void strassen_matrix_multiplication_rect_memopt(float** C, const float* const* const A, const float* const* const B,
                                                size_t Arow, size_t Acol, size_t Bcol);

#endif  //__STRASSEN__
