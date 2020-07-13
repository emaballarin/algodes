#include "matrix.h"
#include "util.h"

/*
 * this function performs the element-wise
 * subtraction of B from A and put the resulting
 * sub-matrix in C. The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void sub_matrix_blocks(float** C, float const* const* const A, float const* const* const B, const size_t C_f_row,
                       const size_t C_f_col, const size_t A_f_row, const size_t A_f_col, const size_t B_f_row,
                       const size_t B_f_col, const size_t n)
{
    for (size_t y = 0; y < n; y++)
    {
        for (size_t x = 0; x < n; x++)
        {
            C[y + C_f_row][x + C_f_col] = A[y + A_f_row][x + A_f_col] - B[y + B_f_row][x + B_f_col];
        }
    }
}

/*
 * this function performs the element-wise
 * sum of A and B and put the resulting
 * sub-matrix in C. The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void sum_matrix_blocks(float** C, float const* const* const A, float const* const* const B, const size_t C_f_row,
                       const size_t C_f_col, const size_t A_f_row, const size_t A_f_col, const size_t B_f_row,
                       const size_t B_f_col, const size_t n)
{
    for (size_t y = 0; y < n; y++)
    {
        for (size_t x = 0; x < n; x++)
        {
            C[y + C_f_row][x + C_f_col] = A[y + A_f_row][x + A_f_col] + B[y + B_f_row][x + B_f_col];
        }
    }
}

void zero_matrix_block(float** C, const size_t C_f_row, const size_t C_f_col, const size_t Crow, const size_t Ccol)
{
    for (size_t i = C_f_row; i < Crow; i++)
    {
        for (size_t j = C_f_col; j < Ccol; j++)
        {
            C[i][j] = 0;
        }
    }
}

/*
 * this function implements the naive algorithm
 * for matrix multiplication between sub-matrixes.
 * The result is placed in the sub-matrix C.
 * The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void naive_aux(float** C, float const* const* const A, float const* const* const B, const size_t C_f_row,
               const size_t C_f_col, const size_t A_f_row, const size_t A_f_col, const size_t B_f_row,
               const size_t B_f_col, const size_t n)
{
    for (size_t y = 0; y < n; y++)
    {
        for (size_t x = 0; x < n; x++)
        {
            float value = 0.0;
            for (size_t z = 0; z < n; z++)
            {
                value += A[y + A_f_row][z + A_f_col] * B[z + B_f_row][x + B_f_col];
            }

            C[y + C_f_row][x + C_f_col] = value;
        }
    }
}

/*
 * This function implements the Strassen's algorithm
 * for matrix multiplication between sub-matrixes.
 * The result is placed in the sub-matrix C.
 * The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void strassen_aux(float** C, float const* const* const A, float const* const* const B, const size_t C_f_row,
                  const size_t C_f_col, const size_t A_f_row, const size_t A_f_col, const size_t B_f_row,
                  const size_t B_f_col, const size_t n)
{
    if (n <= (1 << 6))
    {
        naive_aux(C, A, B, C_f_row, C_f_col, A_f_row, A_f_col, B_f_row, B_f_col, n);

        return;
    }

    size_t n2 = n / 2;  // This is the size of the blocks

    float*** S = (float***)malloc(sizeof(float**) * 10);
    for (size_t i = 0; i < 10; i++)
    {
        S[i] = allocate_matrix(n2, n2);
    }

    float*** P = (float***)malloc(sizeof(float**) * 7);
    for (size_t i = 0; i < 7; i++)
    {
        P[i] = allocate_matrix(n2, n2);
    }

    // S1 = B12 - B22
    sub_matrix_blocks(S[0], B, B, 0, 0, B_f_row, B_f_col + n2, B_f_row + n2, B_f_col + n2, n2);

    // P1 = A11 x S1
    strassen_aux(P[0], A, (const float* const* const)S[0], 0, 0, A_f_row, A_f_col, 0, 0, n2);

    // S2 = A11 + A12
    sum_matrix_blocks(S[1], A, A, 0, 0, A_f_row, A_f_col, A_f_row, A_f_col + n2, n2);


    // P2 = S2 x B22
    strassen_aux(P[1], (const float* const* const)S[1], B, 0, 0, 0, 0, B_f_row + n2, B_f_col + n2, n2);

    // S3 = A21 + A22
    sum_matrix_blocks(S[2], A, A, 0, 0, A_f_row + n2, A_f_col, A_f_row + n2, A_f_col + n2, n2);

    // P3 = S3 x B11
    strassen_aux(P[2], (const float* const* const)S[2], B, 0, 0, 0, 0, B_f_row, B_f_col, n2);

    // S4 = B21 - B11
    sub_matrix_blocks(S[3], B, B, 0, 0, B_f_row + n2, B_f_col, B_f_row, B_f_col, n2);

    // P4 = A22 x S4
    strassen_aux(P[3], A, (const float* const* const)S[3], 0, 0, A_f_row + n2, A_f_col + n2, 0, 0, n2);

    // S5 = A11 + A22
    sum_matrix_blocks(S[4], A, A, 0, 0, A_f_row, A_f_col, A_f_row + n2, A_f_col + n2, n2);

    // S6 = B11 + B22
    sum_matrix_blocks(S[5], B, B, 0, 0, B_f_row, B_f_col, B_f_row + n2, B_f_col + n2, n2);

    // P5 = S5 x S6
    strassen_aux(P[4], (const float* const* const)S[4], (const float* const* const)S[5], 0, 0, 0, 0, 0, 0, n2);

    // S7 = A12 - A22
    sub_matrix_blocks(S[6], A, A, 0, 0, A_f_row, A_f_col + n2, A_f_row + n2, A_f_col + n2, n2);

    // S8 = B21 + B22
    sum_matrix_blocks(S[7], B, B, 0, 0, B_f_row + n2, B_f_col, B_f_row + n2, B_f_col + n2, n2);

    // P6 = S7 x S8
    strassen_aux(P[5], (const float* const* const)S[6], (const float* const* const)S[7], 0, 0, 0, 0, 0, 0, n2);

    // S9 = A11 - A21
    sub_matrix_blocks(S[8], A, A, 0, 0, A_f_row, A_f_col, A_f_row + n2, A_f_col, n2);

    // S10 = B11 + B12
    sum_matrix_blocks(S[9], B, B, 0, 0, B_f_row, B_f_col, B_f_row, B_f_col + n2, n2);

    // P7 = S9 x S10
    strassen_aux(P[6], (const float* const* const)S[8], (const float* const* const)S[9], 0, 0, 0, 0, 0, 0, n2);

    // C11 = P5 + P4 - P2 + P6
    sum_matrix_blocks(C, (const float* const* const)P[4], (const float* const* const)P[3], C_f_row, C_f_col, 0, 0, 0, 0,
                      n2);
    sub_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[1], C_f_row, C_f_col, C_f_row,
                      C_f_col, 0, 0, n2);
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[5], C_f_row, C_f_col, C_f_row,
                      C_f_col, 0, 0, n2);

    // C12 = P1 + P2
    sum_matrix_blocks(C, (const float* const* const)P[0], (const float* const* const)P[1], C_f_row, C_f_col + n2, 0, 0,
                      0, 0, n2);

    // C21 = P3 + P4
    sum_matrix_blocks(C, (const float* const* const)P[2], (const float* const* const)P[3], C_f_row + n2, C_f_col, 0, 0,
                      0, 0, n2);

    // C22 = P5 + P1 - P3 - P7
    sum_matrix_blocks(C, (const float* const* const)P[4], (const float* const* const)P[0], C_f_row + n2, C_f_col + n2,
                      0, 0, 0, 0, n2);
    sub_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[2], C_f_row + n2, C_f_col + n2,
                      C_f_row + n2, C_f_col + n2, 0, 0, n2);
    sub_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[6], C_f_row + n2, C_f_col + n2,
                      C_f_row + n2, C_f_col + n2, 0, 0, n2);

    for (size_t i = 0; i < 10; i++)
    {
        deallocate_matrix(S[i], n2);
    }
    free(S);

    for (size_t i = 0; i < 7; i++)
    {
        deallocate_matrix(P[i], n2);
    }
    free(P);
}

void strassen_aux_odd(float** C, float const* const* const A, float const* const* const B, const size_t C_f_row,
                      const size_t C_f_col, const size_t A_f_row, const size_t A_f_col, const size_t B_f_row,
                      const size_t B_f_col, const size_t n)
{
    if (n <= 65)
    {
        naive_aux(C, A, B, C_f_row, C_f_col, A_f_row, A_f_col, B_f_row, B_f_col, n);

        return;
    }

    if (n % 2)
    {
        // Pad
        float** Apad = pad_new((float const* const* const)A, n, n, n + 1, n + 1, A_f_row, A_f_col);
        float** Bpad = pad_new((float const* const* const)B, n, n, n + 1, n + 1, B_f_row, B_f_col);
        float** Ctemp = allocate_matrix(n + 1, n + 1);

        // Multiply
        strassen_aux_odd(Ctemp, (float const* const* const)Apad, (float const* const* const)Bpad, 0, 0, 0, 0, 0, 0,
                         n + 1);

        // Copy-back
        unpad(C, (float const* const* const)Ctemp, n + 1, n + 1, n, n, C_f_row, C_f_col);

        // Tidy memory
        deallocate_matrix(Apad, n + 1);
        deallocate_matrix(Bpad, n + 1);
        deallocate_matrix(Ctemp, n + 1);

        return;
    }

    size_t n2 = n / 2;  // This is the size of the blocks

    float*** S = (float***)malloc(sizeof(float**) * 10);
    for (size_t i = 0; i < 10; i++)
    {
        S[i] = allocate_matrix(n2, n2);
    }

    float*** P = (float***)malloc(sizeof(float**) * 7);
    for (size_t i = 0; i < 7; i++)
    {
        P[i] = allocate_matrix(n2, n2);
    }

    // S1 = B12 - B22
    sub_matrix_blocks(S[0], B, B, 0, 0, B_f_row, B_f_col + n2, B_f_row + n2, B_f_col + n2, n2);

    // P1 = A11 x S1
    strassen_aux_odd(P[0], A, (const float* const* const)S[0], 0, 0, A_f_row, A_f_col, 0, 0, n2);

    // S2 = A11 + A12
    sum_matrix_blocks(S[1], A, A, 0, 0, A_f_row, A_f_col, A_f_row, A_f_col + n2, n2);


    // P2 = S2 x B22
    strassen_aux_odd(P[1], (const float* const* const)S[1], B, 0, 0, 0, 0, B_f_row + n2, B_f_col + n2, n2);

    // S3 = A21 + A22
    sum_matrix_blocks(S[2], A, A, 0, 0, A_f_row + n2, A_f_col, A_f_row + n2, A_f_col + n2, n2);

    // P3 = S3 x B11
    strassen_aux_odd(P[2], (const float* const* const)S[2], B, 0, 0, 0, 0, B_f_row, B_f_col, n2);

    // S4 = B21 - B11
    sub_matrix_blocks(S[3], B, B, 0, 0, B_f_row + n2, B_f_col, B_f_row, B_f_col, n2);

    // P4 = A22 x S4
    strassen_aux_odd(P[3], A, (const float* const* const)S[3], 0, 0, A_f_row + n2, A_f_col + n2, 0, 0, n2);

    // S5 = A11 + A22
    sum_matrix_blocks(S[4], A, A, 0, 0, A_f_row, A_f_col, A_f_row + n2, A_f_col + n2, n2);

    // S6 = B11 + B22
    sum_matrix_blocks(S[5], B, B, 0, 0, B_f_row, B_f_col, B_f_row + n2, B_f_col + n2, n2);

    // P5 = S5 x S6
    strassen_aux_odd(P[4], (const float* const* const)S[4], (const float* const* const)S[5], 0, 0, 0, 0, 0, 0, n2);

    // S7 = A12 - A22
    sub_matrix_blocks(S[6], A, A, 0, 0, A_f_row, A_f_col + n2, A_f_row + n2, A_f_col + n2, n2);

    // S8 = B21 + B22
    sum_matrix_blocks(S[7], B, B, 0, 0, B_f_row + n2, B_f_col, B_f_row + n2, B_f_col + n2, n2);

    // P6 = S7 x S8
    strassen_aux_odd(P[5], (const float* const* const)S[6], (const float* const* const)S[7], 0, 0, 0, 0, 0, 0, n2);

    // S9 = A11 - A21
    sub_matrix_blocks(S[8], A, A, 0, 0, A_f_row, A_f_col, A_f_row + n2, A_f_col, n2);

    // S10 = B11 + B12
    sum_matrix_blocks(S[9], B, B, 0, 0, B_f_row, B_f_col, B_f_row, B_f_col + n2, n2);

    // P7 = S9 x S10
    strassen_aux_odd(P[6], (const float* const* const)S[8], (const float* const* const)S[9], 0, 0, 0, 0, 0, 0, n2);

    // C11 = P5 + P4 - P2 + P6
    sum_matrix_blocks(C, (const float* const* const)P[4], (const float* const* const)P[3], C_f_row, C_f_col, 0, 0, 0, 0,
                      n2);
    sub_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[1], C_f_row, C_f_col, C_f_row,
                      C_f_col, 0, 0, n2);
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[5], C_f_row, C_f_col, C_f_row,
                      C_f_col, 0, 0, n2);

    // C12 = P1 + P2
    sum_matrix_blocks(C, (const float* const* const)P[0], (const float* const* const)P[1], C_f_row, C_f_col + n2, 0, 0,
                      0, 0, n2);

    // C21 = P3 + P4
    sum_matrix_blocks(C, (const float* const* const)P[2], (const float* const* const)P[3], C_f_row + n2, C_f_col, 0, 0,
                      0, 0, n2);

    // C22 = P5 + P1 - P3 - P7
    sum_matrix_blocks(C, (const float* const* const)P[4], (const float* const* const)P[0], C_f_row + n2, C_f_col + n2,
                      0, 0, 0, 0, n2);
    sub_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[2], C_f_row + n2, C_f_col + n2,
                      C_f_row + n2, C_f_col + n2, 0, 0, n2);
    sub_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[6], C_f_row + n2, C_f_col + n2,
                      C_f_row + n2, C_f_col + n2, 0, 0, n2);

    for (size_t i = 0; i < 10; i++)
    {
        deallocate_matrix(S[i], n2);
    }
    free(S);

    for (size_t i = 0; i < 7; i++)
    {
        deallocate_matrix(P[i], n2);
    }
    free(P);
}

// A memory-constrained (== minimal memory; some performance loss) implementation of the Strassen algorithm
void strassen_aux_odd_memc(float** C, float const* const* const A, float const* const* const B, const size_t C_f_row,
                           const size_t C_f_col, const size_t A_f_row, const size_t A_f_col, const size_t B_f_row,
                           const size_t B_f_col, const size_t n)
{
    if (n <= 65)
    {
        naive_aux(C, A, B, C_f_row, C_f_col, A_f_row, A_f_col, B_f_row, B_f_col, n);

        return;
    }

    if (n % 2)
    {
        // Pad
        float** Apad = pad_new((float const* const* const)A, n, n, n + 1, n + 1, A_f_row, A_f_col);
        float** Bpad = pad_new((float const* const* const)B, n, n, n + 1, n + 1, B_f_row, B_f_col);
        float** Ctemp = allocate_matrix(n + 1, n + 1);

        // Multiply
        strassen_aux_odd_memc(Ctemp, (float const* const* const)Apad, (float const* const* const)Bpad, 0, 0, 0, 0, 0, 0,
                              n + 1);

        // Copy-back
        unpad(C, (float const* const* const)Ctemp, n + 1, n + 1, n, n, C_f_row, C_f_col);

        // Tidy memory
        deallocate_matrix(Apad, n + 1);
        deallocate_matrix(Bpad, n + 1);
        deallocate_matrix(Ctemp, n + 1);

        return;
    }

    size_t n2 = n / 2;  // This is the size of the blocks

    float*** S = (float***)malloc(sizeof(float**) * 2);
    S[0] = allocate_matrix(n2, n2);
    S[1] = allocate_matrix(n2, n2);


    float*** P = (float***)malloc(sizeof(float**));
    P[0] = allocate_matrix(n2, n2);

    // Set to zero the C matrix blocks which will contain the result!
    zero_matrix_block(C, C_f_row, C_f_col, C_f_row + n, C_f_col + n);


    // S1 = B12 - B22
    sub_matrix_blocks(S[0], B, B, 0, 0, B_f_row, B_f_col + n2, B_f_row + n2, B_f_col + n2, n2);

    // P1 = A11 x S1
    strassen_aux_odd_memc(P[0], A, (const float* const* const)S[0], 0, 0, A_f_row, A_f_col, 0, 0, n2);

    // Lay down P1 on C12
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col + n2, C_f_row,
                      C_f_col + n2, 0, 0, n2);

    // Lay down P1 on C22
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + n2, C_f_col + n2,
                      C_f_row + n2, C_f_col + n2, 0, 0, n2);


    // S2 = A11 + A12
    sum_matrix_blocks(S[0], A, A, 0, 0, A_f_row, A_f_col, A_f_row, A_f_col + n2, n2);

    // P2 = S2 x B22
    strassen_aux_odd_memc(P[0], (const float* const* const)S[0], B, 0, 0, 0, 0, B_f_row + n2, B_f_col + n2, n2);

    // Lay down P2 on C11
    sub_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col, C_f_row,
                      C_f_col, 0, 0, n2);

    // Lay down P2 on C12
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col + n2, C_f_row,
                      C_f_col + n2, 0, 0, n2);


    // S3 = A21 + A22
    sum_matrix_blocks(S[0], A, A, 0, 0, A_f_row + n2, A_f_col, A_f_row + n2, A_f_col + n2, n2);

    // P3 = S3 x B11
    strassen_aux_odd_memc(P[0], (const float* const* const)S[0], B, 0, 0, 0, 0, B_f_row, B_f_col, n2);

    // Lay down P3 on C21
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + n2, C_f_col,
                      C_f_row + n2, C_f_col, 0, 0, n2);

    // Lay down P3 on C22
    sub_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + n2, C_f_col + n2,
                      C_f_row + n2, C_f_col + n2, 0, 0, n2);


    // S4 = B21 - B11
    sub_matrix_blocks(S[0], B, B, 0, 0, B_f_row + n2, B_f_col, B_f_row, B_f_col, n2);

    // P4 = A22 x S4
    strassen_aux_odd_memc(P[0], A, (const float* const* const)S[0], 0, 0, A_f_row + n2, A_f_col + n2, 0, 0, n2);

    // Lay down P4 on C21
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + n2, C_f_col,
                      C_f_row + n2, C_f_col, 0, 0, n2);

    // Lay down P4 on C11
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col, C_f_row,
                      C_f_col, 0, 0, n2);


    // S5 = A11 + A22
    sum_matrix_blocks(S[0], A, A, 0, 0, A_f_row, A_f_col, A_f_row + n2, A_f_col + n2, n2);

    // S6 = B11 + B22
    sum_matrix_blocks(S[1], B, B, 0, 0, B_f_row, B_f_col, B_f_row + n2, B_f_col + n2, n2);

    // P5 = S5 x S6
    strassen_aux_odd_memc(P[0], (const float* const* const)S[0], (const float* const* const)S[1], 0, 0, 0, 0, 0, 0, n2);

    // Lay down P5 on C11
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col, C_f_row,
                      C_f_col, 0, 0, n2);

    // Lay down P5 on C22
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + n2, C_f_col + n2,
                      C_f_row + n2, C_f_col + n2, 0, 0, n2);


    // S7 = A12 - A22
    sub_matrix_blocks(S[0], A, A, 0, 0, A_f_row, A_f_col + n2, A_f_row + n2, A_f_col + n2, n2);

    // S8 = B21 + B22
    sum_matrix_blocks(S[1], B, B, 0, 0, B_f_row + n2, B_f_col, B_f_row + n2, B_f_col + n2, n2);

    // P6 = S7 x S8
    strassen_aux_odd_memc(P[0], (const float* const* const)S[0], (const float* const* const)S[1], 0, 0, 0, 0, 0, 0, n2);

    // Lay down P6 on C11
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col, C_f_row,
                      C_f_col, 0, 0, n2);


    // S9 = A11 - A21
    sub_matrix_blocks(S[0], A, A, 0, 0, A_f_row, A_f_col, A_f_row + n2, A_f_col, n2);

    // S10 = B11 + B12
    sum_matrix_blocks(S[1], B, B, 0, 0, B_f_row, B_f_col, B_f_row, B_f_col + n2, n2);

    // P7 = S9 x S10
    strassen_aux_odd_memc(P[0], (const float* const* const)S[0], (const float* const* const)S[1], 0, 0, 0, 0, 0, 0, n2);


    // S matrices no longer needed
    deallocate_matrix(S[0], n2);
    deallocate_matrix(S[1], n2);
    free(S);

    // Lay down P7 on C22
    sub_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + n2, C_f_col + n2,
                      C_f_row + n2, C_f_col + n2, 0, 0, n2);

    // P matrices no longer needed
    deallocate_matrix(P[0], n2);
    free(P);
}

// Here the goal is to maximize memory efficiency, while keeping performance at best
void strassen_aux_odd_memopt(float** C, float const* const* const A, float const* const* const B, const size_t C_f_row,
                             const size_t C_f_col, const size_t A_f_row, const size_t A_f_col, const size_t B_f_row,
                             const size_t B_f_col, const size_t n)
{
    if (n <= 65)
    {
        naive_aux(C, A, B, C_f_row, C_f_col, A_f_row, A_f_col, B_f_row, B_f_col, n);

        return;
    }

    if (n % 2)
    {
        // Pad
        float** Apad = pad_new((float const* const* const)A, n, n, n + 1, n + 1, A_f_row, A_f_col);
        float** Bpad = pad_new((float const* const* const)B, n, n, n + 1, n + 1, B_f_row, B_f_col);
        float** Ctemp = allocate_matrix(n + 1, n + 1);

        // Multiply
        strassen_aux_odd_memopt(Ctemp, (float const* const* const)Apad, (float const* const* const)Bpad, 0, 0, 0, 0, 0,
                                0, n + 1);

        // Copy-back
        unpad(C, (float const* const* const)Ctemp, n + 1, n + 1, n, n, C_f_row, C_f_col);

        // Tidy memory
        deallocate_matrix(Apad, n + 1);
        deallocate_matrix(Bpad, n + 1);
        deallocate_matrix(Ctemp, n + 1);

        return;
    }

    size_t n2 = n / 2;  // This is the size of the blocks

    float*** S = (float***)malloc(sizeof(float**) * 2);
    S[0] = allocate_matrix(n2, n2);
    S[1] = allocate_matrix(n2, n2);


    float*** P = (float***)malloc(sizeof(float**) * 3);
    P[0] = allocate_matrix(n2, n2);
    P[1] = allocate_matrix(n2, n2);
    P[2] = allocate_matrix(n2, n2);

    // S1 = B12 - B22
    sub_matrix_blocks(S[0], B, B, 0, 0, B_f_row, B_f_col + n2, B_f_row + n2, B_f_col + n2, n2);

    // P1 = A11 x S1
    strassen_aux_odd_memopt(P[0], A, (const float* const* const)S[0], 0, 0, A_f_row, A_f_col, 0, 0, n2);


    // S2 = A11 + A12
    sum_matrix_blocks(S[0], A, A, 0, 0, A_f_row, A_f_col, A_f_row, A_f_col + n2, n2);

    // P2 = S2 x B22
    strassen_aux_odd_memopt(P[1], (const float* const* const)S[0], B, 0, 0, 0, 0, B_f_row + n2, B_f_col + n2, n2);


    // C12 = P1 + P2
    sum_matrix_blocks(C, (const float* const* const)P[0], (const float* const* const)P[1], C_f_row, C_f_col + n2, 0, 0,
                      0, 0, n2);


    // S3 = A21 + A22
    sum_matrix_blocks(S[0], A, A, 0, 0, A_f_row + n2, A_f_col, A_f_row + n2, A_f_col + n2, n2);

    // P3 = S3 x B11
    strassen_aux_odd_memopt(P[2], (const float* const* const)S[0], B, 0, 0, 0, 0, B_f_row, B_f_col, n2);

    // C22 = P1 - P3 + ...
    sub_matrix_blocks(C, (const float* const* const)P[0], (const float* const* const)P[2], C_f_row + n2, C_f_col + n2,
                      0, 0, 0, 0, n2);


    // S4 = B21 - B11
    sub_matrix_blocks(S[0], B, B, 0, 0, B_f_row + n2, B_f_col, B_f_row, B_f_col, n2);

    // P4 = A22 x S4
    strassen_aux_odd_memopt(P[0], A, (const float* const* const)S[0], 0, 0, A_f_row + n2, A_f_col + n2, 0, 0, n2);


    // C21 = P3 + P4
    sum_matrix_blocks(C, (const float* const* const)P[2], (const float* const* const)P[0], C_f_row + n2, C_f_col, 0, 0,
                      0, 0, n2);

    // P3 no longer needed
    deallocate_matrix(P[2], n2);

    // C11 = P4 - P2 + ...
    sub_matrix_blocks(C, (const float* const* const)P[0], (const float* const* const)P[1], C_f_row, C_f_col, 0, 0, 0, 0,
                      n2);

    // P2 no longer needed
    deallocate_matrix(P[1], n2);

    // S5 = A11 + A22
    sum_matrix_blocks(S[0], A, A, 0, 0, A_f_row, A_f_col, A_f_row + n2, A_f_col + n2, n2);

    // S6 = B11 + B22
    sum_matrix_blocks(S[1], B, B, 0, 0, B_f_row, B_f_col, B_f_row + n2, B_f_col + n2, n2);

    // P5 = S5 x S6
    strassen_aux_odd_memopt(P[0], (const float* const* const)S[0], (const float* const* const)S[1], 0, 0, 0, 0, 0, 0,
                            n2);

    // C11 = P5 + ...
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col, C_f_row,
                      C_f_col, 0, 0, n2);

    // C22 = P5 + ...
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + n2, C_f_col + n2,
                      C_f_row + n2, C_f_col + n2, 0, 0, n2);


    // S7 = A12 - A22
    sub_matrix_blocks(S[0], A, A, 0, 0, A_f_row, A_f_col + n2, A_f_row + n2, A_f_col + n2, n2);

    // S8 = B21 + B22
    sum_matrix_blocks(S[1], B, B, 0, 0, B_f_row + n2, B_f_col, B_f_row + n2, B_f_col + n2, n2);

    // P6 = S7 x S8
    strassen_aux_odd_memopt(P[0], (const float* const* const)S[0], (const float* const* const)S[1], 0, 0, 0, 0, 0, 0,
                            n2);

    // C11 = P6 + ...
    sum_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col, C_f_row,
                      C_f_col, 0, 0, n2);

    // S9 = A11 - A21
    sub_matrix_blocks(S[0], A, A, 0, 0, A_f_row, A_f_col, A_f_row + n2, A_f_col, n2);

    // S10 = B11 + B12
    sum_matrix_blocks(S[1], B, B, 0, 0, B_f_row, B_f_col, B_f_row, B_f_col + n2, n2);

    // P7 = S9 x S10
    strassen_aux_odd_memopt(P[0], (const float* const* const)S[0], (const float* const* const)S[1], 0, 0, 0, 0, 0, 0,
                            n2);

    // S matrices no longer needed
    deallocate_matrix(S[0], n2);
    deallocate_matrix(S[1], n2);
    free(S);


    // C22 = ... - P7
    sub_matrix_blocks(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + n2, C_f_col + n2,
                      C_f_row + n2, C_f_col + n2, 0, 0, n2);

    // P matrices no longer needed
    deallocate_matrix(P[0], n2);
    free(P);
}

void strassen_matrix_multiplication_rect(float** C, const float* const* const A, const float* const* const B,
                                         size_t Arow, size_t Acol, size_t Bcol)
{
    // Get the smallest side-size
    size_t minsize = getmin(getmin(Arow, Acol), Bcol);

    // Pad A, B to allow being slided on with a minsize-side square matrix
    size_t ApadRow = ((Arow - 1) / minsize + 1) * minsize;
    size_t ApadCol = ((Acol - 1) / minsize + 1) * minsize;
    size_t BpadCol = ((Bcol - 1) / minsize + 1) * minsize;

    // Pad & Allocate
    float** Apad = pad_new(A, Arow, Acol, ApadRow, ApadCol, 0, 0);
    float** Bpad = pad_new(B, Acol, Bcol, ApadCol, BpadCol, 0, 0);
    float** Cout = callocate_matrix(ApadRow, BpadCol);

    // Slide-multiply

    float** Ctemp = allocate_matrix(minsize, minsize);

    for (size_t i = 0; i < ApadRow; i += minsize)
    {
        for (size_t j = 0; j < BpadCol; j += minsize)
        {
            for (size_t k = 0; k < ApadCol; k += minsize)
            {
                strassen_aux_odd(Ctemp, (const float* const* const)Apad, (const float* const* const)Bpad, 0, 0, i, k, k,
                                 j, minsize);
                sum_matrix_blocks(Cout, (const float* const* const)Cout, (const float* const* const)Ctemp, i, j, i, j,
                                  0, 0, minsize);
                zero_matrix(Ctemp, minsize, minsize);
            }
        }
    }

    unpad(C, (const float* const* const)Cout, ApadRow, BpadCol, Arow, Bcol, 0, 0);

    deallocate_matrix(Apad, ApadRow);
    deallocate_matrix(Bpad, ApadCol);
    deallocate_matrix(Cout, ApadRow);
    deallocate_matrix(Ctemp, minsize);
}

void strassen_matrix_multiplication_rect_memc(float** C, const float* const* const A, const float* const* const B,
                                              size_t Arow, size_t Acol, size_t Bcol)
{
    // Get the smallest side-size
    size_t minsize = getmin(getmin(Arow, Acol), Bcol);

    // Pad A, B to allow being slided on with a minsize-side square matrix
    size_t ApadRow = ((Arow - 1) / minsize + 1) * minsize;
    size_t ApadCol = ((Acol - 1) / minsize + 1) * minsize;
    size_t BpadCol = ((Bcol - 1) / minsize + 1) * minsize;

    // Pad & Allocate
    float** Apad = pad_new(A, Arow, Acol, ApadRow, ApadCol, 0, 0);
    float** Bpad = pad_new(B, Acol, Bcol, ApadCol, BpadCol, 0, 0);
    float** Cout = callocate_matrix(ApadRow, BpadCol);

    // Slide-multiply

    float** Ctemp = allocate_matrix(minsize, minsize);

    for (size_t i = 0; i < ApadRow; i += minsize)
    {
        for (size_t j = 0; j < BpadCol; j += minsize)
        {
            for (size_t k = 0; k < ApadCol; k += minsize)
            {
                strassen_aux_odd_memc(Ctemp, (const float* const* const)Apad, (const float* const* const)Bpad, 0, 0, i,
                                      k, k, j, minsize);
                sum_matrix_blocks(Cout, (const float* const* const)Cout, (const float* const* const)Ctemp, i, j, i, j,
                                  0, 0, minsize);
                zero_matrix(Ctemp, minsize, minsize);
            }
        }
    }

    unpad(C, (const float* const* const)Cout, ApadRow, BpadCol, Arow, Bcol, 0, 0);

    deallocate_matrix(Apad, ApadRow);
    deallocate_matrix(Bpad, ApadCol);
    deallocate_matrix(Cout, ApadRow);
    deallocate_matrix(Ctemp, minsize);
}

void strassen_matrix_multiplication_rect_memopt(float** C, const float* const* const A, const float* const* const B,
                                                size_t Arow, size_t Acol, size_t Bcol)
{
    // Get the smallest side-size
    size_t minsize = getmin(getmin(Arow, Acol), Bcol);

    // Pad A, B to allow being slided on with a minsize-side square matrix
    size_t ApadRow = ((Arow - 1) / minsize + 1) * minsize;
    size_t ApadCol = ((Acol - 1) / minsize + 1) * minsize;
    size_t BpadCol = ((Bcol - 1) / minsize + 1) * minsize;

    // Pad & Allocate
    float** Apad = pad_new(A, Arow, Acol, ApadRow, ApadCol, 0, 0);
    float** Bpad = pad_new(B, Acol, Bcol, ApadCol, BpadCol, 0, 0);
    float** Cout = callocate_matrix(ApadRow, BpadCol);

    // Slide-multiply

    float** Ctemp = allocate_matrix(minsize, minsize);

    for (size_t i = 0; i < ApadRow; i += minsize)
    {
        for (size_t j = 0; j < BpadCol; j += minsize)
        {
            for (size_t k = 0; k < ApadCol; k += minsize)
            {
                strassen_aux_odd_memopt(Ctemp, (const float* const* const)Apad, (const float* const* const)Bpad, 0, 0,
                                        i, k, k, j, minsize);
                sum_matrix_blocks(Cout, (const float* const* const)Cout, (const float* const* const)Ctemp, i, j, i, j,
                                  0, 0, minsize);
                zero_matrix(Ctemp, minsize, minsize);
            }
        }
    }

    unpad(C, (const float* const* const)Cout, ApadRow, BpadCol, Arow, Bcol, 0, 0);

    deallocate_matrix(Apad, ApadRow);
    deallocate_matrix(Bpad, ApadCol);
    deallocate_matrix(Cout, ApadRow);
    deallocate_matrix(Ctemp, minsize);
}

/*
 * this functions is exclusively meant to provide an
 * easy to use API
 */
void strassen_matrix_multiplication(float** C, float const* const* const A, float const* const* const B, size_t n)
{

    strassen_aux(C, A, B, 0, 0, 0, 0, 0, 0, n);
}

void strassen_matrix_multiplication_odd(float** C, float const* const* const A, float const* const* const B, size_t n)
{

    strassen_aux_odd(C, A, B, 0, 0, 0, 0, 0, 0, n);
}
