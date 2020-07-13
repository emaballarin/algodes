#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

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

void naive_matrix_multiplication_gen(float** C, float const* const* const A, float const* const* const B,
                                     const size_t Arow, const size_t Acol, const size_t Bcol)
{
    for (size_t y = 0; y < Arow; y++)
    {
        for (size_t x = 0; x < Bcol; x++)
        {
            float value = 0.0;
            for (size_t z = 0; z < Acol; z++)
            {
                value += A[y][z] * B[z][x];
            }

            C[y][x] = value;
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

float** callocate_matrix(const size_t rows, const size_t cols)
{
    float** M = (float**)malloc(sizeof(float*) * rows);

    for (size_t i = 0; i < rows; i++)
    {
        M[i] = (float*)calloc(cols, sizeof(float));
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
