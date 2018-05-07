/**************************************************************
    Problem: 4011
    User: SysCon
    Language: C++
    Result: Accepted
    Time:988 ms
    Memory:11532 kb
****************************************************************/
 
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 220007
#define MAX_M 220007
#define MOD 1000000007
typedef long long ll;
 
int N, M, adx, ady;
int head[MAX_N], to[MAX_M], nxt[MAX_M], cap;
int deg[MAX_N], c[MAX_N],  _deg[MAX_N];
int top[MAX_N], t;
ll f[MAX_N], res = 1;
ll ine[MAX_N];
 
void add_edge (int, int, int);
void get_ine (int);
void solve ();
 
int main () {
    scanf("%d%d%d%d", &N, &M, &adx, &ady);
    int u, v;
    for (int i = 1;i <= M; ++i) {
    scanf("%d%d", &u, &v);
    add_edge(u, v, 0);
    deg[v]++;
    }
    deg[ady]++;
    for (int i = 2;i <= N; ++i)
    res = (res * deg[i]) % MOD;
    if (ady == 1) {printf("%lld\n", res);return 0;}
    get_ine(M + 1);
    solve();
    return 0;
}
 
void solve () {
    int q[MAX_M];
    int r = 0, h = 0;
    for (int i = 1;i <= N; ++i) {
    if (!deg[i]) q[++r] = i;
    _deg[i] = deg[i];
    }
    f[ady] = res % MOD;
    deg[ady]--;
    while (r != h) {
    int x = q[++h];
    f[x] = f[x] * ine[_deg[x]] % MOD;
    for (int i = head[x]; i; i = nxt[i]) {
        f[to[i]] = (f[to[i]] + f[x]) % MOD;
        if (!(--deg[to[i]])) q[++r] = to[i];
    } 
    }
    //for (int i = 2;i <= N; ++i) printf("%d ", f[i]); printf("\n");
    printf("%d\n", (res - f[adx] + MOD) % MOD);
}
 
void get_ine (int n) {
    ine[1] = 1;
    for (int i = 2;i <= n; ++i)
    ine[i] = ((MOD - MOD / i) * ine[MOD % i]) % MOD;
}
 
void add_edge (int u, int v, int op) {
    nxt[++cap] = head[u];
    head[u] = cap;
    to[cap] = v;
} 
