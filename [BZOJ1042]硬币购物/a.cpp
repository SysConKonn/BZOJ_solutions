#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 1000010
using namespace std;

long long c[5], d[5], N, res, t;
long long f[MAX_N];

void dfs (int x, int k, int sum) {
    if (sum < 0) return;
    if (x == 5) {  //奇减偶加
	if (k & 1) res -= f[sum];
	else res += f[sum];
	return;
    }
    dfs(x + 1, k + 1, sum - (d[x] + 1) * c[x]);
    dfs(x + 1, k, sum);
}

int main () {
    for (int i = 1;i <= 4; ++i) scanf("%lld", c + i);
    f[0] = 1;
    for (int i = 1;i <= 4; ++i)
	for (int j = c[i];j <= MAX_N; ++j)
	    f[j] += f[j - c[i]];
    scanf("%lld", &N);
    for (int i = 1;i <= N; ++i) {
	for (int i = 1;i <= 4; ++i) scanf("%lld", d + i);
	scanf("%lld", &t);res = 0;
	dfs(1, 0, t);
	printf("%lld\n", res);
    }
    return 0;
}
