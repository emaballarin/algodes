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
    for (size_t j = 50; j <= n; j += 1)
    {

        printf("%ld\t", j);
        fflush(stdout);

        printf("%lf\t", test_rect(strassen_adapter_rect, C1, A, B, j, j+1, j+2));
        fflush(stdout);
        printf("%lf\t", test_rect(naive_matrix_multiplication_rect, C1, A, B, j, j + 1, j + 2));
        fflush(stdout);

        printf("%d\n", same_matrix((float const* const* const)C0, (float const* const* const)C1, j, j));

        if (j == 10)
        {
            return 0;
            /*printf("\n");
            print_matrix(C0)
            printf("\n"); */
        }
    }

    deallocate_matrix(A, n);
    deallocate_matrix(B, n);
    deallocate_matrix(C0, n);
    deallocate_matrix(C1, n);

    return 0;
}
