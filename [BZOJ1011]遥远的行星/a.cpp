#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 100007

int N;
double a;
double m[MAX_N], p[MAX_N];
double res[MAX_N];
int pos;

void solve_sml () {
    for (int i = 1;i <= std::min(N, 2000); ++i) {
        if ((double)a * i + 1e-8 >= (double)(pos + 1)) pos++;
        for (int j = 1;j <= pos; ++j)
            res[i] += m[i] * m[j] / (double)(i - j);
    }
}

int main () {
    scanf("%d%lf", &N, &a);
    for (int i = 1;i <= N; ++i) scanf("%lf", m + i), p[i] = p[i - 1] + m[i];
    solve_sml();
    for (int i = 2001;i <= N; ++i) {
        if ((double)a * i + 1e-8 >= (double)(pos + 1)) pos++;
        //pos = i * a + 1e-8;
        res[i] = p[pos] * m[i] / (double)(i - (int)pos / 2);
    }
    for (int i = 1;i <= N; ++i) printf("%.6lf\n", res[i]);
    return 0;
}
