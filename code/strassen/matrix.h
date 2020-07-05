#ifndef __MATRIX__
    #include <stdlib.h>

void naive_matrix_multiplication(float** C, float const* const* const A, float const* const* const B, const size_t n);
void naive_matrix_multiplication_rect(float** C, float const* const* const A, float const* const* const B,
                                      const size_t Arow, const size_t Acol, const size_t Bcol);

int same_matrix(float const* const* const A, float const* const* const B, const size_t rows, const size_t cols);

float** allocate_matrix(const size_t rows, const size_t cols);
float** callocate_matrix(const size_t rows, const size_t cols);
void deallocate_matrix(float** A, const size_t rows);

float** allocate_random_matrix(const size_t rows, const size_t cols);


float** pad_new(float const* const* const ORIG, const size_t Orows, const size_t Ocols, const size_t Nrows,
                const size_t Ncols, const size_t RowSeek, const size_t ColSeek);
void unpad(float** UNPADDED, float const* const* const ORIG, const size_t Orows, const size_t Ocols, const size_t Nrows,
           const size_t Ncols, const size_t FromRow, const size_t FromCol);

void zero_matrix(float** C, size_t rows, const size_t cols);

// Diagnostics
void print_matrix(float** C, size_t rows, const size_t cols);

#endif  //__MATRIX__
