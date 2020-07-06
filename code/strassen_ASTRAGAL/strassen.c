#include "matrix.h"
#include "util.h"

#include <stdio.h>

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

void sub_matrix_blocks_gen(float** C, float const* const* const A, float const* const* const B, const size_t C_f_row,
                           const size_t C_f_col, const size_t A_f_row, const size_t A_f_col, const size_t B_f_row,
                           const size_t B_f_col, const size_t Rows, const size_t Cols)
{
    for (size_t y = 0; y < Rows; y++)
    {
        for (size_t x = 0; x < Cols; x++)
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

void sum_matrix_blocks_gen(float** C, float const* const* const A, float const* const* const B, const size_t C_f_row,
                           const size_t C_f_col, const size_t A_f_row, const size_t A_f_col, const size_t B_f_row,
                           const size_t B_f_col, const size_t Rows, const size_t Cols)
{
    for (size_t y = 0; y < Rows; y++)
    {
        for (size_t x = 0; x < Cols; x++)
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

void naive_aux_gen(float** C, float const* const* const A, float const* const* const B, const size_t C_f_row,
                   const size_t C_f_col, const size_t A_f_row, const size_t A_f_col, const size_t B_f_row,
                   const size_t B_f_col, const size_t Arow, const size_t Acol, const size_t Bcol)
{
    for (size_t y = 0; y < Arow; y++)
    {
        for (size_t x = 0; x < Bcol; x++)
        {
            float value = 0.0;
            for (size_t z = 0; z < Acol; z++)
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


void strassen_aux_gen(float** C, float const* const* const A, float const* const* const B, const size_t C_f_row,
                      const size_t C_f_col, const size_t A_f_row, const size_t A_f_col, const size_t B_f_row,
                      const size_t B_f_col, const size_t Arow, const size_t Acol, const size_t Bcol)
{
    if (((Arow <= (1 << 6)) && (Acol <= (1 << 6)) && (Bcol <= (1 << 6))) || (Arow == 1) || (Acol == 1) || (Bcol == 1))
    {
        naive_aux_gen(C, A, B, C_f_row, C_f_col, A_f_row, A_f_col, B_f_row, B_f_col, Arow, Acol, Bcol);
        return;
    }

    // Set to zero the C matrix blocks which will contain the result!
    zero_matrix_block(C, C_f_row, C_f_col, C_f_row + Arow, C_f_col + Bcol);

    // ODD-RECTANGULAR STRASSEN WITH DYNAMIC PEELING
    size_t aro = Arow % 2, aco = Acol % 2, bco = Bcol % 2;
    if (aro || aco || bco)
    {
        // C11 <- A11 x B11
        strassen_aux_gen(C, A, B, C_f_row, C_f_col, A_f_row, A_f_col, B_f_row, B_f_col, Arow - aro, Acol - aco,
                         Bcol - bco);


        // A Rows ODD
        if (aro)
        {
            // C21 <- a21 x B11
            strassen_aux_gen(C, A, B, C_f_row + (Arow - aro), C_f_col, A_f_row + Arow - aro, A_f_col, B_f_row, B_f_col,
                             1, Acol - aco, Bcol - bco);
        }

        if (aro && aco)
        {
            // BL
            // a22 x b21
            float** BL = allocate_matrix(1, Bcol - bco);
            strassen_aux_gen(BL, A, B, 0, 0, A_f_row + Arow - aro, A_f_col + Acol - aco, B_f_row + Acol - aco, B_f_col,
                             1, 1, Bcol - bco);
            sum_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)BL, C_f_row + Arow - aro,
                                  C_f_col, C_f_row + Arow - aro, C_f_col, 0, 0, 1, Bcol - bco);
            deallocate_matrix(BL, 1);
        }

        if (aro && bco)
        {
            // C22 <- a21 x b12
            strassen_aux_gen(C, A, B, C_f_row + Arow - aro, C_f_col + Bcol - bco, A_f_row + Arow - aro, A_f_col,
                             B_f_row, B_f_col + Bcol - bco, 1, Acol - aco, 1);
        }

        // A Cols ODD <-> B Rows ODD
        if (aco)
        {
            // TL
            // a12 x b21
            float** TL = allocate_matrix(Arow - aro, Bcol - bco);
            strassen_aux_gen(TL, A, B, 0, 0, A_f_row, A_f_col + Acol - aco, B_f_row + Acol - aco, B_f_col, Arow - aro,
                             1, Bcol - bco);
            sum_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)TL, C_f_row, C_f_col,
                                  C_f_row, C_f_col, 0, 0, Arow - aro, Bcol - bco);
            deallocate_matrix(TL, Arow - aro);
        }

        // B Cols ODD
        if (bco)
        {
            // C12 <- A11 x b12
            strassen_aux_gen(C, A, B, C_f_row, C_f_col + (Bcol - bco), A_f_row, A_f_col, B_f_row, B_f_col + Bcol - bco,
                             Arow - aro, Acol - aco, 1);
        }

        if (bco && aco)
        {
            // TR
            // a12 x b22
            float** TR = allocate_matrix(Arow - aro, 1);
            strassen_aux_gen(TR, A, B, 0, 0, A_f_row, A_f_col + Acol - aco, B_f_row + Acol - aco, B_f_col + Bcol - bco,
                             Arow - aro, 1, 1);
            sum_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)TR, C_f_row,
                                  C_f_col + Bcol - bco, C_f_row, C_f_col + Bcol - bco, 0, 0, Arow - aro, 1);
            deallocate_matrix(TR, Arow - aro);
        }

        if (aro && aco && bco)
        {
            // BR
            // a22 x b22
            float** BR = allocate_matrix(1, 1);
            strassen_aux_gen(BR, A, B, 0, 0, A_f_row + Arow - aro, A_f_col + Acol - aco, B_f_row + Acol - aco,
                             B_f_col + Bcol - bco, 1, 1, 1);
            sum_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)BR, C_f_row + Arow - aro,
                                  C_f_col + Bcol - bco, C_f_row + Arow - aro, C_f_col + Bcol - bco, 0, 0, 1, 1);
            deallocate_matrix(BR, 1);
        }
        return;
    }

    // EVEN-RECTANGULAR STRASSEN

    size_t AR2 = Arow / 2;
    size_t AC2 = Acol / 2;
    size_t BC2 = Bcol / 2;

    size_t maxside = getmax(getmax(AR2, AC2), BC2);

    float*** S = (float***)malloc(sizeof(float**) * 2);
    S[0] = allocate_matrix(maxside, maxside);
    S[1] = allocate_matrix(maxside, maxside);


    float*** P = (float***)malloc(sizeof(float**));
    P[0] = allocate_matrix(maxside, maxside);

    // S1 = B12 - B22
    sub_matrix_blocks_gen(S[0], B, B, 0, 0, B_f_row, B_f_col + BC2, B_f_row + AC2, B_f_col + BC2, AC2, BC2);

    // P1 = A11 x S1
    strassen_aux_gen(P[0], A, (const float* const* const)S[0], 0, 0, A_f_row, A_f_col, 0, 0, AR2, AC2, BC2);

    // Lay down P1 on C12
    sum_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col + BC2,
                          C_f_row, C_f_col + BC2, 0, 0, AR2, BC2);

    // Lay down P1 on C22
    sum_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + AR2,
                          C_f_col + BC2, C_f_row + AR2, C_f_col + BC2, 0, 0, AR2, BC2);


    // S2 = A11 + A12
    sum_matrix_blocks_gen(S[0], A, A, 0, 0, A_f_row, A_f_col, A_f_row, A_f_col + AC2, AR2, AC2);

    // P2 = S2 x B22
    strassen_aux_gen(P[0], (const float* const* const)S[0], B, 0, 0, 0, 0, B_f_row + AC2, B_f_col + BC2, AR2, AC2, BC2);

    // Lay down P2 on C11
    sub_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col, C_f_row,
                          C_f_col, 0, 0, AR2, BC2);

    // Lay down P2 on C12
    sum_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col + BC2,
                          C_f_row, C_f_col + BC2, 0, 0, AR2, BC2);


    // S3 = A21 + A22
    sum_matrix_blocks_gen(S[0], A, A, 0, 0, A_f_row + AR2, A_f_col, A_f_row + AR2, A_f_col + AC2, AR2, AC2);

    // P3 = S3 x B11
    strassen_aux_gen(P[0], (const float* const* const)S[0], B, 0, 0, 0, 0, B_f_row, B_f_col, AR2, AC2, BC2);

    // Lay down P3 on C21
    sum_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + AR2, C_f_col,
                          C_f_row + AR2, C_f_col, 0, 0, AR2, BC2);

    // Lay down P3 on C22
    sub_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + AR2,
                          C_f_col + BC2, C_f_row + AR2, C_f_col + BC2, 0, 0, AR2, BC2);


    // S4 = B21 - B11
    sub_matrix_blocks_gen(S[0], B, B, 0, 0, B_f_row + AC2, B_f_col, B_f_row, B_f_col, AC2, BC2);

    // P4 = A22 x S4
    strassen_aux_gen(P[0], A, (const float* const* const)S[0], 0, 0, A_f_row + AR2, A_f_col + AC2, 0, 0, AR2, AC2, BC2);

    // Lay down P4 on C21
    sum_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + AR2, C_f_col,
                          C_f_row + AR2, C_f_col, 0, 0, AR2, BC2);

    // Lay down P4 on C11
    sum_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col, C_f_row,
                          C_f_col, 0, 0, AR2, BC2);


    // S5 = A11 + A22
    sum_matrix_blocks_gen(S[0], A, A, 0, 0, A_f_row, A_f_col, A_f_row + AR2, A_f_col + AC2, AR2, AC2);

    // S6 = B11 + B22
    sum_matrix_blocks_gen(S[1], B, B, 0, 0, B_f_row, B_f_col, B_f_row + AC2, B_f_col + BC2, AC2, BC2);

    // P5 = S5 x S6
    strassen_aux_gen(P[0], (const float* const* const)S[0], (const float* const* const)S[1], 0, 0, 0, 0, 0, 0, AR2, AC2,
                     BC2);

    // Lay down P5 on C11
    sum_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col, C_f_row,
                          C_f_col, 0, 0, AR2, BC2);

    // Lay down P5 on C22
    sum_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + AR2,
                          C_f_col + BC2, C_f_row + AR2, C_f_col + BC2, 0, 0, AR2, BC2);


    // S7 = A12 - A22
    sub_matrix_blocks_gen(S[0], A, A, 0, 0, A_f_row, A_f_col + AC2, A_f_row + AR2, A_f_col + AC2, AR2, AC2);

    // S8 = B21 + B22
    sum_matrix_blocks_gen(S[1], B, B, 0, 0, B_f_row + AC2, B_f_col, B_f_row + AC2, B_f_col + BC2, AC2, BC2);

    // P6 = S7 x S8
    strassen_aux_gen(P[0], (const float* const* const)S[0], (const float* const* const)S[1], 0, 0, 0, 0, 0, 0, AR2, AC2,
                     BC2);

    // Lay down P6 on C11
    sum_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row, C_f_col, C_f_row,
                          C_f_col, 0, 0, AR2, BC2);


    // S9 = A11 - A21
    sub_matrix_blocks_gen(S[0], A, A, 0, 0, A_f_row, A_f_col, A_f_row + AR2, A_f_col, AR2, AC2);

    // S10 = B11 + B12
    sum_matrix_blocks_gen(S[1], B, B, 0, 0, B_f_row, B_f_col, B_f_row, B_f_col + BC2, AC2, BC2);

    // P7 = S9 x S10
    strassen_aux_gen(P[0], (const float* const* const)S[0], (const float* const* const)S[1], 0, 0, 0, 0, 0, 0, AR2, AC2,
                     BC2);


    // S matrices no longer needed
    deallocate_matrix(S[0], maxside);
    deallocate_matrix(S[1], maxside);
    free(S);

    // Lay down P7 on C22
    sub_matrix_blocks_gen(C, (const float* const* const)C, (const float* const* const)P[0], C_f_row + AR2,
                          C_f_col + BC2, C_f_row + AR2, C_f_col + BC2, 0, 0, AR2, BC2);

    // P matrices no longer needed
    deallocate_matrix(P[0], maxside);
    free(P);
}


/*
 * this functions is exclusively meant to provide an
 * easy to use API
 */
void strassen_matrix_multiplication(float** C, float const* const* const A, float const* const* const B, size_t n)
{

    strassen_aux(C, A, B, 0, 0, 0, 0, 0, 0, n);
}

void strassen_matrix_multiplication_gen(float** C, float const* const* const A, float const* const* const B,
                                        size_t Arow, size_t Acol, size_t Bcol)
{

    strassen_aux_gen(C, A, B, 0, 0, 0, 0, 0, 0, Arow, Acol, Bcol);
}
