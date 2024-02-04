#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

void fast_fourier_transform(double complex *x, int N) {
  if (N == 1) {
    return;
  }
  double complex *even =
      (double complex *)malloc(N / 2 * sizeof(double complex));
  double complex *odd =
      (double complex *)malloc(N / 2 * sizeof(double complex));

  for (int i = 0; i < N / 2; i++) {
    even[i] = x[2 * i];
    odd[i] = x[2 * i + 1];
  }

  fast_fourier_transform(even, N / 2);
  fast_fourier_transform(odd, N / 2);

  for (int j = 0; j < N / 2; j++) {
    double complex t = cexp(-2 * PI * I * j / N) * odd[j];
    x[j] = even[j] + t;
    x[j + N / 2] = even[j] - t;
  }

  free(even);
  free(odd);
}
int main() {
  int N = 100000;
  double complex *x = (double complex *)malloc(N * sizeof(double complex));
  for (int i = 0; i < N; i++) {
    x[i] =
        rand() / (double)RAND_MAX - 0.5 + I * (rand() / (double)RAND_MAX - 0.5);
  }

  fast_fourier_transform(x, N);

  free(x);
  return 0;
}