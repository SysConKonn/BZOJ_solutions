#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#define MAX_N 110
#define MAX_M 21
#define MAX_E 410
#define INF 21474836
using namespace std;

int N, M, k, e;
int head[MAX_N], to[MAX_E], nxt[MAX_E], dis[MAX_E], tmp;
bool cant_use[MAX_M][MAX_N], vis[MAX_N], inq[MAX_N];
int cost[MAX_N][MAX_N], d[MAX_M], f[MAX_N];

void add_edge (int, int, int);
void mark (int, int, int);
void spfa (int, int);

int main () {
    scanf("%d%d%d%d", &N, &M, &k, &e);
    int u, v, w;
    for (int i = 1;i <= e; ++i) {
	scanf("%d%d%d", &u, &v, &w);
	add_edge (u, v, w);
	add_edge (v, u, w);
    }
    memset(cant_use, false, sizeof(cant_use));
    int d, idx, l, r;
    scanf("%d", &d);
    for (int i = 1;i <= d; ++i) scanf("%d%d%d", &idx, &l, &r), mark(idx, l, r);
    for (int ld = 1;ld <= N; ++ld) 
	for (int rd = ld;rd <= N; ++rd)
	    spfa (ld, rd);
    
    /*
    for (int i = 1;i <= N; ++i)
	for (int j = i;j <= N; ++j)
	    printf("%d %d %d\n", i, j, cost[i][j]);
    */
    // for (int i = 1;i <= N; ++i) f[i] = cost[1][i] * i;
    for (int i = 1;i <= N; ++i) f[i] = cost[1][i] * i;
    f[0] = -k;
    for (int i = 2; i <= N; ++i) {
	int mn = INF;
	for (int j = 0;j < i; ++j)
	    f[i] = min(f[i], f[j] + cost[j + 1][i] * (i - j) + k);
    }
    // for (int i = 1;i <= N; ++i) printf("%d ", f[i]); printf("\n");
    printf("%d\n", f[N]);
    return 0;
}

void spfa (int l, int r) {
    memset(vis, false, sizeof(vis));
    memset(inq, false, sizeof(inq));
    for (int i = l;i <= r; ++i)
	for (int j = 1;j <= M; ++j)
	    if (cant_use[j][i]) vis[j] = true;
    fill (d + 1, d + M + 1, INF);
    d[1] = 0;
    queue<int> q;
    q.push(1), inq[1] = true;
    while (!q.empty()) {
	int x = q.front(); q.pop();
	inq[x] = false;
	if (vis[x]) continue;
	for (int i = head[x]; i; i = nxt[i]) {
	    if (vis[to[i]]) continue;
	    if (d[to[i]] > d[x] + dis[i]) {
		d[to[i]] = d[x] + dis[i];
		if (!inq[to[i]]) q.push(to[i]), inq[to[i]] = true;
	    }
	}
    }
    // for (int i = 1;i <= M; ++i) printf("%d ", d[i]); printf("\n");
    cost[l][r] = d[M];
}

void mark (int id, int l, int r) {
    for (int i = l;i <= r; ++i) cant_use[id][i] = true;
}

void add_edge (int u, int v, int w) {
    nxt[++tmp] = head[u];
    head[u] = tmp;
    to[tmp] = v;
    dis[tmp] = w;
}
