#ifndef __MATRIX__
    #include <stdlib.h>

void naive_matrix_multiplication(float** C, float const* const* const A, float const* const* const B, const size_t n);
void naive_matrix_multiplication_gen(float** C, float const* const* const A, float const* const* const B,
                                     const size_t Arow, const size_t Acol, const size_t Bcol);

int same_matrix(float const* const* const A, float const* const* const B, const size_t rows, const size_t cols);

float** allocate_matrix(const size_t rows, const size_t cols);
float** callocate_matrix(const size_t rows, const size_t cols);
void deallocate_matrix(float** A, const size_t rows);
float** allocate_random_matrix(const size_t rows, const size_t cols);

#endif  //__MATRIX__
