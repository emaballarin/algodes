#include "matrix.h"
#include "strassen.h"
#include "test.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
    size_t n = 1 << 9;

    float** A = allocate_random_matrix(n, n);
    float** B = allocate_random_matrix(n, n);
    float** C0 = allocate_matrix(n, n);
    float** C1 = allocate_matrix(n, n);
    float** C2 = allocate_matrix(n, n);
    float** C3 = allocate_matrix(n, n);


    printf("n\tSt. Alg. (cl)\tSt. Alg. (opt)\tSt. Alg. (mc)\tNaive Alg.\tS.R. (cl)\tS.R. (opt)\tS.R. (mc)\n");
    for (size_t j = 64; j <= n; j = j*2 + 3)
    {

        printf("%ld\t", j);
        fflush(stdout);

        printf("%lf\t", test_rect(strassen_matrix_multiplication_rect, C1, A, B, j, j+1, j+2));
        fflush(stdout);

        printf("%lf\t", test_rect(strassen_matrix_multiplication_rect_memopt, C2, A, B, j, j + 1, j + 2));
        fflush(stdout);

        printf("%lf\t", test_rect(strassen_matrix_multiplication_rect_memc, C3, A, B, j, j + 1, j + 2));
        //printf("%lf\t", test(strassen_matrix_multiplication_odd, C1, A, B, j));

        fflush(stdout);
        printf("%lf\t", test_rect(naive_matrix_multiplication_rect, C0, A, B, j, j+1, j+2));
        //printf("%lf\t", test(naive_matrix_multiplication, C0, A, B, j));

        fflush(stdout);
        printf("%d\t\t", same_matrix((float const* const* const)C0, (float const* const* const)C1, j, j+2));

        fflush(stdout);
        printf("%d\t\t", same_matrix((float const* const* const)C0, (float const* const* const)C2, j, j + 2));

        fflush(stdout);
        printf("%d\n", same_matrix((float const* const* const)C0, (float const* const* const)C3, j, j + 2));
        //printf("%d\n", same_matrix((float const* const* const)C0, (float const* const* const)C1, j, j));
    }

    deallocate_matrix(A, n);
    deallocate_matrix(B, n);
    deallocate_matrix(C0, n);
    deallocate_matrix(C1, n);
    deallocate_matrix(C2, n);
    deallocate_matrix(C3, n);

    return 0;
}
