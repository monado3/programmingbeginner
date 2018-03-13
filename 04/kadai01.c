#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
  調和級数 \sum_{i=1}^{n}(1 / i)
*/
double harmonic(int n) {
  double j;
  double sum;
  for (j = 1.0;j <= n;j++) {
    sum +=  1.0 / j;
  }

  return sum;
}

int main() {
  double sum = 0;
  int i;
  int upto = 5;
  double log_val;
  double harmonic_val;
  int N;

  for (i = 0;i <= upto;i++) {
    N = (int) pow(10, i);
    log_val = log(N + 1);
    harmonic_val = harmonic(N);
    printf("%f, %f\n", log_val, harmonic_val);
  }

  return 0;
}
