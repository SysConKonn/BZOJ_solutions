#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 500010
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
int l, lim = 1, r[MAX_N * 4];
int x_[MAX_N], y_[MAX_N], c, cnt;
int A, B, D, res = INF, ans[MAX_N * 4];
int mx;

void fft (complex*, int);
double max (double a, double b);
double min (int a, int b);

int main () {
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    
    scanf("%d%d", &N, &M);
    while (lim <= N * 2) lim <<= 1, l++;
    for (int i = 0;i < lim; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    
    for (int i = 0;i < N; ++i) scanf("%d", x_ + i);
    for (int i = 0;i < N; ++i) scanf("%d", y_ + i);
    for (int i = 0;i < N; ++i) B -= x_[i];
    for (int i = 0;i < N; ++i) B += y_[i];
    if (B > 0) c = (int)((double)B / (double)N + 0.5);
    else c = (int)((double)B / (double)N - 0.5);
    for (int i = 0;i < N; ++i) x_[i] += c;
    
    for (int i = 0;i < N; ++i) a[i].x = (double)x_[i];
    for (int i = 0;i < N; ++i) b[i].x = (double)y_[N - i - 1];
    
    fft(a, 1);
    fft(b, 1);
    for (int i = 0;i < lim; ++i) a[i] = a[i] * b[i];
    fft(a, -1);
    for (int i = 0;i < N; ++i) ans[i] += (int)(a[N - i - 1].x / (double)lim + 0.5);
    //for (int i = 0;i < N; ++i) printf("%d ", ans[i]);printf("\n");
    //for (int i = 0;i < lim; ++i) printf("%lf ", x[i].x); printf("\n");
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));

    for (int i = 0;i < N; ++i) a[i].x = (double)x_[N - i - 1];
    for (int i = 0;i < N; ++i) b[i].x = (double)y_[i];
    //for (int i = 0;i < N; ++i) printf("%lf %lf\n", a[i].x, b[i].x);
    fft(a, 1);
    fft(b, 1);
    for (int i = 0;i < lim; ++i) a[i] = a[i] * b[i];
    fft(a, -1);
    for (int i = 0;i < N; ++i) ans[i] += (int)(i == 0 ? 0 : (a[i - 1].x / (double)lim) + 0.5);
    for (int i = 0;i < N; ++i) mx = std::max(mx, ans[i]);
    //for (int i = 0;i < N; ++i) printf("%d ", ans[i]);printf("\n");
    //printf("%d %d %d %lf\n", B, D, c, mx);
    mx *= 2;
    mx *= -1;
    for (int i = 0;i < N; ++i) mx += x_[i] * x_[i] + y_[i] * y_[i];
    res = std::min(mx, res);
    printf("%d\n", res);
    return 0;
}

double min (int a, int b) {return a < b ? a : b;}
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
