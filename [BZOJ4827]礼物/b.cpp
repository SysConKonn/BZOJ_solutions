#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 400010
#define PI acos(-1)
#define INF 2147483647

struct complex {
    double x, y;
    complex (double x_ = 0, double y_ = 0) {x = x_, y = y_;}
}x[MAX_N * 4], y[MAX_N * 4], a[MAX_N * 4], b[MAX_N * 4];

complex operator + (complex a, complex b) {return complex(a.x + b.x, a.y + b.y);}
complex operator - (complex a, complex b) {return complex(a.x - b.x, a.y - b.y);}
complex operator * (complex a, complex b) {return complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);}

int N, M;
int l, lim = 1, r[MAX_N];
double x_[MAX_N], y_[MAX_N], c;

void fft (complex*, int);
double max (double a, double b);
double min (double a, double b);

int main () {
    scanf("%d%d", &N, &M);
    //part1 : x(reverse), y
    //part2 : a, b(reverse)
    for (int i = 0;i < N; ++i) scanf("%lf", &x[i].x), a[i] = x[i];
    for (int i = 0;i < N; ++i) scanf("%lf", &y[i].x), b[N - i - 1] = y[i];
    for (int i = 0;i < N; ++i) x_[i] = x[i].x, y_[i] = y[i].x;
    for (int i = 0;i < N; ++i) x[i] = a[N - i - 1];

    // for (int i = 0;i < N; ++i) printf("%lf ", x[i].x);printf("\n");
    // for (int i = 0;i < N; ++i) printf("%lf ", y[i].x);printf("\n");
    // for (int i = 0;i < N; ++i) printf("%lf ", a[i].x);printf("\n");
    // for (int i = 0;i < N; ++i) printf("%lf ", b[i].x);printf("\n");

    while (lim <= N * 2) lim <<= 1, l++;
    for (int i = 0;i < lim; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    
    fft(x, 1);
    fft(y, 1);
    for (int i = 0;i < lim; ++i) x[i] = x[i] * y[i];
    fft(x, -1);
    for (int i = 0;i < lim; ++i) x[i].x = (int)(x[i].x / (double)lim + 0.5);
    //for (int i = 0;i < lim; ++i) printf("%lf ", x[i].x); printf("\n");

    fft(a, 1);
    fft(b, 1);
    for (int i = 0;i < lim; ++i) a[i] = a[i] * b[i];
    fft(a, -1);
    for (int i = 0;i < lim; ++i) a[i].x = (int)(a[i].x / (double)lim + 0.5);

    //f(c)=a*c^2+b*c+d
    //-b/2a
    double A = N, B = 0, D = 0;
    for (int i = 0;i < N; ++i) B += x_[i] - y_[i], D += x_[i] * x_[i] + y_[i] * y_[i];
    B *= 2;
    c = B > 0 ? -(int)((double)B / (double)N - 0.5) : -(int)((double)B / (double)N + 0.5);
    //c = (int)min(-B / A / 2, -B / A / 2 + 1);
    double mx = 0;
    for (int i = 0;i < lim; ++i) mx = max(mx, x[N - i - 1].x + (i == 0 ? : a[i - 1].x));
    D -= 2 * mx;
    //printf("%lf %lf %lf %lf\n", A, B, D, A * c * c + B * c);
    printf("%lf %lf %lf\n", B, D, c);
    int res = (int)(A * c * c + B * c + D);
    for (int i = -5;i <= 5; ++i)
	    res = min(res, A * (c + i) * (c + i) + B * (c + i) + D);
    printf("%d\n", res);
    return 0;
}

double min (double a, double b) {return a < b ? a : b;}
double max (double a, double b) {return a < b ? b : a;}

void fft (complex *A, int type) {
    for (int i = 0;i < lim; ++i)
	if (i < r[i]) std::swap(A[i], A[r[i]]);

    for (int mid = 1;mid < lim; mid <<= 1) {
	complex Wn = complex(cos(PI / mid), type * sin(PI / mid));

	for (int R = mid << 1, j = 0;j < lim; j += R) {
	    complex w = complex(1, 0);

	    for (int k = 0;k < mid; ++k, w = w * Wn) {
		complex x = A[k + j], y = A[k + mid + j];
		A[k + j] = x + w * y, A[k + mid + j] = x - w * y;
	    }
	}
    }
}
