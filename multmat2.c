#include <x86intrin.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

int main(int argc, char** argv)
{
    float *matrixA = malloc(SIZE*SIZE*sizeof(float));
    float *matrixB = malloc(SIZE*SIZE*sizeof(float));
    float result[SIZE][SIZE];
    __m128 va, vb, vresult;

    //initialize matrix
    for(int i = 0; i < (SIZE*SIZE); i++)
    {
        *(matrixA + i) = 0.1f;
        *(matrixB + i) = 0.2f;
    }

    // ini result matrix
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            result[i][j] = 0;
        }
    }

    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < SIZE; k+=4)
            {
                va = _mm_loadu_ps(matrixA+(i*SIZE)+k);
                vb = _mm_loadu_ps(matrixB+(i*SIZE)+k);

                vresult = _mm_mul_ps(va, vb);

                vresult = _mm_hadd_ps(vresult, vresult);
                vresult = _mm_hadd_ps(vresult, vresult);

                result[i][j] += _mm_cvtss_f32(vresult);
            }
        }
    }

    return 0;
}
