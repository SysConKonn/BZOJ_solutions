#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 107
#define MOD 9999973
typedef long long ll;

int N, M;
ll f[MAX_N][MAX_N][MAX_N];
ll res;

int main () {
    scanf("%d%d", &N, &M);
    f[0][0][0] = 1;
    for (int i = 0;i < M; ++i) {
	for (int j = 0;j <= N; ++j) {
	    for (int k = 0;k + j <= N; ++k) {
		f[i + 1][j][k] = (f[i][j][k] + f[i + 1][j][k]) % MOD;
		f[i + 1][j + 1][k] = (1LL * f[i][j][k] * (N - j - k) % MOD + f[i + 1][j + 1][k]) % MOD;
		if (j >= 1)
		    f[i + 1][j - 1][k + 1] = (1LL * f[i][j][k] * j % MOD + f[i + 1][j - 1][k + 1]) % MOD;
		if (j >= 2)
		    f[i + 1][j - 2][k + 2] = (1LL * f[i][j][k] * (j - 1) * j / 2 % MOD + f[i + 1][j - 2][k + 2]) % MOD;
		f[i + 1][j][k + 1] = (1LL * f[i][j][k] * (N - j - k) % MOD * j % MOD + f[i + 1][j][k + 1]) % MOD;
		if (j + k + 1 <= N)
		    f[i + 1][j + 2][k] = (1LL * (N - j - k) * (N - j - k - 1) / 2 % MOD * f[i][j][k] % MOD + f[i + 1][j + 2][k]) % MOD;
	    }
	}
    }
    for (int i = 0;i <= N; ++i)
	for (int j = 0;j + i <= N; ++j)
	    res = (res + f[M][i][j]) % MOD;
    printf("%lld\n", res);
    return 0;
}
