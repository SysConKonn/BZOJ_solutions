#include <cstdio>

void show(int N, double &A[], double &B[]) {
  for(int i = 1;i <= N; ++i) {
    for(int j = 1;j <= N; ++j)
      printf("%lf ", A[i][j]);
    printf("%lf\n", B[i]);
  }
}
