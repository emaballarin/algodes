#include "matrix.h"
#include "strassen.h"
#include "test.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
    size_t n = 1 << 12;

    float** A = allocate_random_matrix(n, n);
    float** B = allocate_random_matrix(n, n);
    float** C0 = allocate_matrix(n, n);
    float** C1 = allocate_matrix(n, n);


    printf("n\tStrassen's Alg.\tNaive Alg.\tSame result\n");
    for (size_t j = 1; j <= n; j *= 2)
    {

        printf("%ld\t", j);
        fflush(stdout);

        printf("%lf\t", test_gen(strassen_matrix_multiplication_gen, C1, A, B, j - 1, j, j + 1));
        fflush(stdout);
        printf("%lf\t", test_gen(naive_matrix_multiplication_gen, C0, A, B, j - 1, j, j + 1));
        fflush(stdout);

        printf("%d\n", same_matrix((float const* const* const)C0, (float const* const* const)C1, j, j));
    }

    deallocate_matrix(A, n);
    deallocate_matrix(B, n);
    deallocate_matrix(C0, n);
    deallocate_matrix(C1, n);

    return 0;
}
