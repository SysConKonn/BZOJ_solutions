#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 61
#define MAX_M 61
using namespace std;

long long N, sr, sb, sg, mod, M;
long long a[MAX_M][MAX_N], f[MAX_N][MAX_N][MAX_N], d[MAX_N];
long long res, sum;
bool vis[MAX_N];
long long nx[MAX_N];

long long dp (int);

int main () {
    scanf("%lld%lld%lld%lld%lld", &sr, &sb, &sg, &M, &mod);
    N = sr + sb + sg;
    for (int i = 1;i <= M; ++i)
	for (int j = 1;j <= N; ++j)
	    scanf("%lld", &a[i][j]);
    M++;
    for (int i = 1;i <= N; ++i) a[M][i] = i;  //还有一种置换方法就是位置全都不改变
    for (int i = 1;i <= M; ++i) res = (res + dp(i) + mod) % mod;
    nx[1] = 1;
    for (int i = 2;i <= M; ++i) nx[i] = (mod + (mod - mod / i) * nx[mod % i]) % mod;
    printf("%lld\n", res * nx[M] % mod);
    return 0;
}

long long dp (int x) {
    memset(f, 0, sizeof(f));
    memset(vis, false, sizeof(vis));
    sum = 0;
    for (int i = 1;i <= N; ++i) {
	if (vis[i]) continue;
	d[++sum] = 1;
	int p = i;vis[p] = true;
	while (!vis[a[x][p]]) {
	    p = a[x][p];
	    vis[p] = true;
	    d[sum]++;
	}
    }
    // printf("%d:\n", x);
    // for (int i = 1;i <= sum; ++i) 
    f[0][0][0] = 1;
    for (int i = 1;i <= sum; ++i)
	for (int j = sr;j >= 0; --j)
	    for (int k = sb; k >= 0; --k)
		for (int t = sg; t >= 0; --t) {
		    if (j >= d[i]) f[j][k][t] = (f[j][k][t] + f[j - d[i]][k][t]) % mod;
		    if (k >= d[i]) f[j][k][t] = (f[j][k][t] + f[j][k - d[i]][t]) % mod;
		    if (t >= d[i]) f[j][k][t] = (f[j][k][t] + f[j][k][t - d[i]]) % mod;
		}
    // printf("%d %d\n", x, f[sr][sb][sg]);
    return f[sr][sb][sg];
}
