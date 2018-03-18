#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#define MAX_N 13
using namespace std;

int N;
double A[MAX_N][MAX_N], B[MAX_N];
double x[MAX_N][MAX_N];   //x[i][j]第i个元素的第j个值
double res[MAX_N];

void gauss () {
  for(int i = 1;i <= N; ++i) {
    int k = i;
    for(int j = i + 1;j <= N; ++j)
      if(fabs(A[k][i]) < fabs(A[j][i])) k = j;
    if(k != i) {
      for(int j = 1;j <= N; ++j) swap(A[i][j], A[k][j]);
      swap(B[i], B[k]);
    }

    for(int j = i + 1;j <= N; ++j) {
      if(A[j][i] == 0) continue;
      long double del = (long double) A[j][i] / A[i][i];
      for(k = 1;k <= N; ++k)
	A[j][k] -= del * A[i][k];
      B[j] -= B[i] * del;
    }
  }

  for(int i = N; i; --i) {
    for(int j = N;j > i; --j) B[i] -= (double) A[i][j] * res[j];
    res[i] = (double) B[i]/A[i][i];
  }

  for(int i = 1;i < N; ++i)
    printf("%.3lf ", res[i]);
  printf("%.3lf", res[N]);
}

int main () {
  scanf("%d", &N);
  for(int i = 1;i <= N + 1; ++i)
    for(int j = 1;j <= N; ++j)
      scanf("%lf", &x[j][i]);
  
  for(int i = 1;i <= N; ++i)   //方阵的第i行
    for(int j = 1;j <= N; ++j)
      A[i][j] = 2 * (x[j][i] - x[j][i + 1]), B[i] += x[j][i] * x[j][i] - x[j][i + 1] * x[j][i + 1];

  // for(int i = 1;i <= N; ++i) {
  //   for(int j = 1;j <= N; ++j)
  //     printf("%lf ", A[i][j]);
  //   printf("%lf\n", B[i]);
  // }

  gauss();
  return 0;
}
