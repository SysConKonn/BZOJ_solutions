#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 100007
#define INF 2147483647

int N, M;
int c[MAX_N];
int head[MAX_N], to[MAX_N * 2], nxt[MAX_N * 2], deg[MAX_N], cap;
int f[MAX_N][2];

void add_edge (int, int);
void dfs (int, int);

int main () {
    scanf("%d%d", &M, &N);
    int u, v;
    for (int i = 1;i <= N; ++i) scanf("%d", c + i);
    for (int i = 1;i < M; ++i) {
	scanf("%d%d", &u, &v), add_edge (u, v), add_edge (v, u);
	deg[u]++, deg[v]++;
    }
    dfs(N + 1, 0);
    // for (int i = 1;i <= M; ++i) printf("%d %d\n", f[i][0], f[i][1]);
    printf("%d\n", std::min(f[N + 1][0], f[N + 1][1]));
    return 0;
}

void dfs (int x, int fa) {
    if (deg[x] == 1) {
	f[x][c[x]] = 1;
	f[x][c[x] ^ 1] = INF;
	return;
    }
    for (int i = head[x]; i; i = nxt[i]) {
	if (to[i] == fa) continue;
	dfs(to[i], x);
	f[x][0] += std::min(f[to[i]][0] - 1, f[to[i]][1]);
	f[x][1] += std::min(f[to[i]][1] - 1, f[to[i]][0]);
    }
    f[x][0]++, f[x][1]++;
}

void add_edge (int u, int v) {
    nxt[++cap] = head[u];
    head[u] = cap;
    to[cap] = v;
}
