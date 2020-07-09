#ifndef __STRASSEN__

void strassen_matrix_multiplication(float** C, float const* const* const A, float const* const* const B, size_t n);
void strassen_matrix_multiplication_gen(float** C, float const* const* const A, float const* const* const B,
                                        size_t Arow, size_t Acol, size_t Bcol);
#endif  //__STRASSEN__
