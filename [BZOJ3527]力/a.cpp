#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 1000010
#define PI acos(-1)

struct complex {
    double x, y;
    complex (double x_ = 0, double y_ = 0) {x = x_, y = y_;}
}a[MAX_N], b[MAX_N], q[MAX_N], c1[MAX_N], c2[MAX_N];

complex operator + (complex a, complex b) {return complex(a.x + b.x, a.y + b.y);}
complex operator - (complex a, complex b) {return complex(a.x - b.x, a.y - b.y);}
complex operator * (complex a, complex b) {return complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);}

int N;
double res[MAX_N];
int lim = 1, l, r[MAX_N];

void fft (complex*, int);

int main () {
    scanf("%d", &N);
    for (int i = 0;i < N; ++i) scanf("%lf", &q[i].x), a[i].x = q[i].x, b[i].x = i == 0 ? 0 : 1.000 / i / i;
    while (lim <= N * 2) lim <<= 1, l++;
    for (int i = 0;i < lim; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    // for (int i = 0;i < lim; ++i) printf("%d ", r[i]); printf("\n");
    fft(a, 1);
    fft(b, 1);
    for (int i = 0;i < lim; ++i) c1[i] = a[i] * b[i];
    //  for (int i = 0;i < lim; ++i) printf("%lf ", c1[i].x / lim); printf("\n");
    memset(a, 0, sizeof(a));
    for (int i = 0;i < N; ++i) a[i] = complex(q[N - i - 1].x, 0);
    //for (int i = 0;i < N; ++i) printf("%lf ", a[i].x); printf("\n");
    fft(a, 1);
    for (int i = 0;i < lim; ++i) c2[i] = a[i] * b[i];
    fft(c1, -1); fft(c2, -1);
    //for (int i = 0;i < N; ++i) printf("%lf\n", c1[i].x / lim); printf("\n");
    //for (int i = N - 1;i >= 0; --i) printf("%lf\n", c2[i].x / lim); printf("\n");
    for (int i = 0;i < N; ++i) printf("%lf\n", c1[i].x / lim - c2[N - i - 1].x / lim);
    return 0;
}

void fft (complex *A, int type) {
    for (int i = 0;i < lim; ++i)
	if (i < r[i]) std::swap(A[i], A[r[i]]);
    for (int mid = 1;mid < lim; mid <<= 1) {
	complex Wn = complex(cos(PI / mid), type * sin(PI / mid));

	for (int R = mid << 1, j = 0;j < lim; j += R) {
	    complex w = complex(1, 0);

	    for (int k = 0;k < mid; ++k, w = w * Wn) {
		complex x = A[j + k], y = A[j + k + mid];
		A[j + k] = x + w * y;
		A[j + k + mid] = x - w * y;
	    }
	}
    }
}
