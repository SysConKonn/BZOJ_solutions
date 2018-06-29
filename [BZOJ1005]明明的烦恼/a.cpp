#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 1005
using namespace std;
struct bignum {
    int num[MAX_N * 100];
    int len;
}res;

int n, tot, m, cnt;
int d[MAX_N], pri[MAX_N], num[MAX_N];

void solve (int, int);
void getprime ();
inline bool jud (int);
void mul (int);

int main () {
    getprime ();
    scanf("%d", &n);
    if (n == 1) {
	scanf("%d", &d[1]);
	if (!d[1]) printf("1\n");
	else printf("0\n");
	return 0;
    }
    for (int i = 1;i <= n; ++i) {
	scanf("%d", &d[i]);
	if (!d[i]) {printf("0\n");return 0;}
	if (d[i] == -1) m++;
	else {d[i]--; tot += d[i];}
    }
    if (tot > n - 2) {printf("0\n"); return 0;}
    solve(n - 2, 1);
    solve(n - 2 - tot, -1);
    for (int i = 1;i <= n; ++i)
	if (d[i] > 0) solve (d[i], -1);
    // for (int i = 1;i <= cnt && pri[i] <= n; ++i) printf("%d %d\n", pri[i], num[i]);
    res.num[1] = res.len = 1;
    for (int i = 1;i <= cnt; ++i)
	while (num[i]--) mul(pri[i]);
    for (int i = 1;i <= n - 2 - tot; ++i) mul(m);
    for (int i = res.len;i > 0; --i) printf("%d", res.num[i]); printf("\n");
    return 0;
}

void mul (int x) {
    for (int i = 1;i <= res.len; ++i) res.num[i] *= x;
    for (int i = 1;i <= res.len; ++i) res.num[i + 1] += res.num[i] / 10, res.num[i] %= 10;
    while (res.num[res.len + 1] > 0) res.len++, res.num[res.len + 1] += res.num[res.len] / 10, res.num[res.len] %= 10;
}

inline bool jud (int x) {
    if (x == 2) return true;
    int sq = sqrt(x) + 1;
    for (int i = 2;i <= sq; ++i) if (x % i == 0) return false;
    return true;
}

void getprime () {
    for (int i = 2;i <= MAX_N; ++i) {
	if (jud (i)) pri[++cnt] = i;
    }
}

void solve (int a, int f) {
    for (int k = 1;k <= a; ++k) {
	int x = k;
	for (int i = 1;i <= cnt; ++i) {
	    if (x <= 1) break;
	    while (x % pri[i] == 0) {num[i] += f; x /= pri[i];}
	}
    }
}
