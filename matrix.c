#include "matrix.h"

#include <stdlib.h>
#include <stdio.h>

/* Módulo de x*/
#define ABS(x) ((x > 0)? (x): -(x))


void matrix_fill_rand(unsigned n, double *restrict _A)
{
    #define A(i, j) _A[n*(i) + (j)]
	int i, j;

	for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            A(i, j) = 10*(double) rand() / (double) RAND_MAX;

    #undef A
}

void matrix_dgemm_0(unsigned n, double *restrict _C, double *restrict _A, double *restrict _B)
{
    /* Macros para acessar os elementos das matrizes mais facilmente*/
    #define A(i, j) _A[n*(i) + (j)]
    #define B(i, j) _B[n*(i) + (j)]
    #define C(i, j) _C[n*(i) + (j)]
    unsigned i, j, k;

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
        {
            double sum = 0;
            for (k = 0; k < n; ++k)
                sum += A(i, k)*B(k, j);
            C(i, j) = sum;
        }

    #undef A
    #undef B
    #undef C
}

void matrix_dgemm_1(unsigned n, double *restrict _C, double *restrict _A, double *restrict _B)
{
    #define A(i, j) _A[n*(i) + (j)]
    #define B(i, j) _B[n*(i) + (j)]
    #define C(i, j) _C[n*(i) + (j)]

    /* Aqui você não deve usar blocagem. Seu código deve ser BEM mais rápido
     * que o anterior (cerca de 10x). */
    /* Seu código aqui. */

    for (int i = 0; i < n; ++i) {
        double col[n];
        for (int j = 0; j < n; ++j)
            col[j] = B(j, i);

        for (int j = 0; j < n; ++j) {
            double sum = 0;

            for (int k = 0; k < n; ++k)
                sum += A(j, k)*col[k];

            C(j, i) = sum;
        }
    }

    #undef A
    #undef B
    #undef C
}

void matrix_dgemm_2(unsigned n, double *restrict _C, double *restrict _A, double *restrict _B)
{
    #define A(i, j) _A[n*(i) + (j)]
    #define B(i, j) _B[n*(i) + (j)]
    #define C(i, j) _C[n*(i) + (j)]

    /* Aqui você deve usar blocagem, em conjunto com a técnica que você
     * desenvolveu em dgemm_1. Dependendo da sua máquina você pode conseguir
     * speedup de 2x em relação ao dgemm_1, Mas não fique triste se você conseguir
     * apenas 1 segundo ou 2.
     */
    /* Seu código aqui. */
    unsigned blockSize = 128;
    unsigned aaa = 16;

    for (int i = 0; i < aaa; ++i) {
        double col[blockSize];

        for (int j = 0; j < blockSize; ++j)
            col[j] = B(j, i);

        for (int j = 0; j < blockSize; ++j) {
            double sum = 0;

            for (int k = 0; k < n; ++k)
                sum += A(j, k)*col[k];

            C(j, i) += sum;
        }
    }

    #undef A
    #undef B
    #undef C
}


bool matrix_eq(unsigned n, double *restrict _A, double *restrict _B)
{
    #define A(i, j) _A[n*(i) + (j)]
    #define B(i, j) _B[n*(i) + (j)]

    unsigned i, j;

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            if (ABS (A(i, j) - B(i, j)) > 1e-15)
                return false;

    return true;
    #undef A
    #undef B
}


bool matrix_which_dgemm(int algorithm, unsigned n,  double *restrict _C,
                        double *restrict _A, double *restrict _B)
{
    bool ret;
    switch(algorithm)
    {
        case 0:
            matrix_dgemm_0(n, _C, _A, _B);
            ret = true;
            break;

        case 1:
            matrix_dgemm_1(n, _C, _A, _B);
            ret = true;
            break;

        case 2:
            matrix_dgemm_2(n, _C, _A, _B);
            ret = true;
            break;

        default:
            ret = false;
    }
    return ret;
}

void print_matrix(unsigned n, double *restrict _M) {
    #define M(i, j) _M[n*(i) + (j)]

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%.2f ", M(i, j));

        printf("\n");
    }
}