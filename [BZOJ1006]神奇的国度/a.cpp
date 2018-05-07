#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 20010
#define MAX_M 1500010
#define F(x) x+N+1

int N, M;
short to[MAX_M * 2];
int head[MAX_N * 2], nxt[MAX_M * 2], cap;
bool vis[MAX_N], mark[MAX_N][1007];
int q[MAX_N], f[MAX_N];
int col[MAX_N], rank[MAX_N], res;

void add_edge (int, int); 
void MCS ();

int main () {
    scanf("%d%d", &N, &M);
    int u, v;
    for (int i = 1;i <= M; ++i) {
	scanf("%d%d", &u, &v);
	add_edge (u, v);
	add_edge (v, u);
    }
    MCS();
    printf("%d\n", res);
    //for (int i = 1;i <= N; ++i) printf("%d ", col[i]); printf("\n");
    return 0;
}

void MCS () {
    memset(vis, false, sizeof(vis));
    memset(q, 0, sizeof(q));
    memset(f, 0, sizeof(f));
    int best = 0;
    for (int i = 1;i <= N; ++i) add_edge(F(0), i);
    for (int t = N;t;--t) {
	int now = 0;
	while (best >= 0) {
	    now = 0;
	    for (int i = head[F(best)]; i; i = nxt[i]) {
		if (!vis[to[i]]) {
		    now = to[i];
		    break;
		}
		else head[F(best)] = nxt[i];
	    }
	    if (now) {
		vis[now] = true;
		q[t] = now;
		for (int i = 1;i;++i)
		    if (!mark[now][i]) {
			col[now] = i;
			res = std::max(res, i);
			break;
		    }
		for (int i = head[now]; i; i = nxt[i]) {
		    if (vis[to[i]]) continue;
		    mark[to[i]][col[now]] = true;
		    f[to[i]]++;
		    best = std::max(best, f[to[i]]);
		    add_edge(F(f[to[i]]), to[i]);
		}
		break;
	    } else best--;
	}
    }
}

void add_edge (int u, int v) {
    nxt[++cap] = head[u];
    head[u] = cap;
    to[cap] = v;
}
