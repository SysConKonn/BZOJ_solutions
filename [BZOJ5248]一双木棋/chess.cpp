#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#define MAX_N 40
typedef long long ll;

int N, M;
ll tot[MAX_N][MAX_N], bsum, pre[MAX_N][MAX_N];
std::map<ll, int> mp;
ll powmp[MAX_N], res;

int chess (ll, int);
int dfs (ll);

int main () {
    //freopen ("chess.in", "r", stdin);
    //freopen ("chess.out", "w", stdout);
    scanf("%d%d", &N, &M);
    powmp[0] = 1;
    for (int i = 1;i <= N; ++i) powmp[i] = powmp[i - 1] * (M + 1);
    ll x;
    for (int i = 1;i <= N; ++i)
	for (int j = 1;j <= M; ++j)
	    scanf("%lld", &x), tot[i][j] += x;
    for (int i = 1;i <= N; ++i)
	for (int j = 1;j <= M; ++j)
	    scanf("%lld", &x), tot[i][j] += x, bsum += x, pre[i][j] = pre[i][j - 1] + tot[i][j];
    res = dfs(0);
    printf("%lld\n", res - bsum);
    return 0;
}

int chess (ll s, int i) {
    if (i == 0) return M;
    return (s / powmp[i - 1]) % (M + 1);
}

int dfs (ll s) {
    if (s == powmp[N] - 1) return 0;
    if (mp[s]) return mp[s];
    int sum = 0, mn = 1000000008;
    int c1 = M, c2 = 0;
    for (int i = 1; i <= N; ++i) {
	c2 = chess(s, i);
	sum += pre[i][M] - pre[i][c2];
	if (c2 < c1) mn = std::min(mn, dfs(s + powmp[i - 1]));
	c1 = c2;
    }
    return mp[s] = sum - mn;
}
