#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 200010
#define INF 214748364700
using namespace std;

struct point {
    double x, y;
}p[MAX_N];

int N, cnt, s[MAX_N];
double res;

void solve (int, int);
double dis (int, int);
double powt (double);
bool cmpx (const point, const point);
bool cmpy (const int, const int);

int main () {
    scanf("%d", &N);
    for (int i = 1;i <= N; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
    sort (p + 1, p + N + 1, cmpx);
    res = INF;
    solve (1, N);
    printf("%0.6lf\n", res);
    return 0;
}

double powt (double x) {return x * x;}

double dis (int x, int y) {
    return sqrt(powt(p[x].x - p[y].x) + powt(p[x].y - p[y].y));
}

void solve (int l, int r) {
    if (l + 1 >= r) return;
    if (l + 2 == r) {res = min(res, dis(l, r) + dis(l + 1, r) + dis(l, r - 1));return;}
    int mid = l + r >> 1;
    solve (l, mid), solve(mid + 1, r); cnt = 0;
    double lim = res / 2.0000000;
    for (int i = l;i <= r; ++i) if (fabs(p[i].x - p[mid].x) <= lim) s[++cnt] = i;
    sort (s + 1, s + cnt + 1, cmpy);
    // printf("%d %d:\n", l, r);
    // for (int i = 1;i <= cnt; ++i) printf("%lf %lf\n", p[s[i]].x, p[s[i]].y);
    for (int i = 1, j = 1;i <= cnt; ++i) {
	for (;j <= cnt && fabs(p[s[j]].y - p[s[i]].y) <= lim; ++j);
	for (int k = i + 1;k < j; ++k)
	    for (int t = i + 1;t < k; ++t)
		res = min(res, dis(s[i], s[k]) + dis(s[k], s[t]) + dis(s[t], s[i]));
    }
}

bool cmpx (const point a, const point b) {return a.x < b.x;}
bool cmpy (const int a, const int b) {return p[a].y < p[b].y;}
