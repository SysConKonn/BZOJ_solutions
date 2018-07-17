#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_M 30
typedef long long ll;

int M;
ll N, K;
char ss[MAX_M];
int s[MAX_M], fail[MAX_M];

struct matrix {
    ll c[MAX_M][MAX_M];
    matrix () {
        memset(c, 0, sizeof(c));
    }
    
    void init () {
        for (int i = 0;i <= M; ++i) c[i][i] = 1;
    }
}mat, ans;

matrix operator * (const matrix a, const matrix b) {
    matrix c;
    for (int i = 0;i <= M; ++i)
        for (int j = 0;j <= M; ++j)
            for (int k = 0;k <= M; ++k)
                (c.c[i][j] += a.c[i][k] * b.c[k][j]) %= K;
    return c;
}

matrix operator % (matrix a, const ll MOD) {
    for (int i = 0;i <= M; ++i)
        for (int j = 0;j <= M; ++j)
            a.c[i][j] %= MOD;
    return a;
}

void quick_pow (matrix x, ll p) {
    ans.init();
    while (p) {
        if (p % 2) 
            ans = (ans * x);
        x = (x * x);
        p >>= 1;
    }
}

int main () {
    scanf("%lld%d%lld", &N, &M, &K);
    scanf("%s", ss);
    for (int i = 1;i <= M; ++i) s[i] = ss[i - 1] - '0';
    for (int i = 2;i <= M; ++i) {
        int j = fail[i - 1];
        while (j && s[j + 1] != s[i]) j = fail[j];
        if (s[j + 1] == s[i]) j++;
        fail[i] = j;
    }
    for (int i = 0;i < M; ++i)
        for (int j = 0;j < 10; ++j) {
            int k = i;
            while (k && s[k + 1] != j) k = fail[k];
            if (s[k + 1] == j) k++;
            if (k != M) (mat.c[i][k] += 1) %= K;
        }
    quick_pow(mat, N);
    ll res = 0;
    for (int i = 0;i < M; ++i)
        (res += ans.c[0][i]) %= K;
    printf("%lld\n", res);
    return 0;
}
