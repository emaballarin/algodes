#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void naive_matrix_multiplication(float** C, float const* const* const A, float const* const* const B, const size_t n)
{
    for (size_t y = 0; y < n; y++)
    {
        for (size_t x = 0; x < n; x++)
        {
            float value = 0.0;
            for (size_t z = 0; z < n; z++)
            {
                value += A[y][z] * B[z][x];
            }

            C[y][x] = value;
        }
    }
}

void naive_matrix_multiplication_rect(float** C, const float* const* const A, const float* const* const B, size_t Arow,
                                      size_t Acol, size_t Bcol)
{
    for (size_t i = 0; i < Arow; i++)
    {
        for (size_t j = 0; j < Bcol; j++)
        {
            float value = 0.0;
            for (size_t k = 0; k < Acol; k++)
            {
                value += A[i][k] * B[k][j];
            }

            C[i][j] = value;
        }
    }
}

int same_matrix(float const* const* const A, float const* const* const B, const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (A[i][j] != B[i][j])
            {
                return 0;
            }
        }
    }

    return 1;
}

float** allocate_matrix(const size_t rows, const size_t cols)
{
    float** M = (float**)malloc(sizeof(float*) * rows);

    for (size_t i = 0; i < rows; i++)
    {
        M[i] = (float*)malloc(sizeof(float) * cols);
    }

    return M;
}

void deallocate_matrix(float** A, const size_t rows)
{
    for (size_t i = 0; i < rows; i++)
    {
        free(A[i]);
    }

    free(A);
}

float** allocate_random_matrix(const size_t rows, const size_t cols)
{

    float** A = allocate_matrix(rows, cols);

    srand(10);
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            A[i][j] = (rand() - RAND_MAX / 2) % 5;
        }
    }

    return A;
}

float** callocate_matrix(const size_t rows, const size_t cols)
{
    float** M = (float**)malloc(sizeof(float*) * rows);

    for (size_t i = 0; i < rows; i++)
    {
        M[i] = (float*)calloc(cols, sizeof(float));
    }

    return M;
}

float** pad_new(float const* const* const ORIG, const size_t Orows, const size_t Ocols, const size_t Nrows,
               const size_t Ncols, const size_t RowSeek, const size_t ColSeek)
{
    assert(Nrows >= Orows);
    assert(Ncols >= Ocols);

    float** PADDED = callocate_matrix(Nrows, Ncols);   // Loop less, calloc more!

    for (size_t i = 0; i < Orows; i++)
    {
        for (size_t j = 0; j < Ocols; j++)
        {
            PADDED[i][j] = ORIG[i+RowSeek][j+ColSeek];
        }
    }

    // And the rest is already zeroed!

    return PADDED;
}

void unpad(float** UNPADDED, float const* const* const ORIG, const size_t Orows, const size_t Ocols, const size_t Nrows, const size_t Ncols, const size_t FromRow, const size_t FromCol)
{
    assert(Nrows <= Orows);
    assert(Ncols <= Ocols);

    for (size_t i = FromRow; i < Nrows + FromRow; ++i)
    {
        for (size_t j = FromCol; j < Ncols + FromCol; ++j)
        {
            UNPADDED[i][j] = ORIG[i][j];
        }
    }

    return;
}

void zero_matrix(float** C, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            C[i][j] = 0;
        }
    }
}

// Diagnostics
void print_matrix(float** C, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            printf("%.2f",C[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}
