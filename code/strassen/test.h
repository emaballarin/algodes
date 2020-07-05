#ifndef __TEST__


double test(void (*f)(float**, float const* const* const, float const* const* const, size_t), float** C, float** A,
            float** B, size_t n);

double test_rect(void (*f)(float**, float const* const* const, float const* const* const, size_t, size_t, size_t),
                 float** C, float** A, float** B, size_t Arow, size_t Acol, size_t Bcol);

#endif  // __TEST__
