#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#define MAX_N 100010
#define INF 2147483647
typedef long long ll;

int N, q;
int head[MAX_N], to[MAX_N * 4], nxt[MAX_N * 4], dis[MAX_N * 4], tmp;
ll res, d[MAX_N];
int cir[MAX_N];
bool inq[MAX_N];

void add_edge (int, int, int);
bool spfa ();

int main () {
    scanf("%d%d", &N, &q);
    int x, a, b;
    for (int i = 1;i <= q; ++i) {
	scanf("%d%d%d", &x, &a, &b);
	if (x == 4) x = 2, std :: swap(a, b);
	if (x == 5) x = 3, std :: swap(a, b);
	if (x == 1) {add_edge (a, b, 0);add_edge (b, a, 0);}
	else if (x == 2) {
	    if (a == b) {printf("-1\n");return 0;}
	    add_edge (a, b, 1);
	}
	else if (x == 3) 
	    add_edge (b, a, 0);
    }
    for (int i = N;i > 0; --i)
	add_edge (0, i, 1);
    if (!spfa()) {printf("-1\n"); return 0;}
    for (int i = 1;i <= N; ++i) res += d[i];
    printf("%lld\n", res);
    return 0;
}

bool spfa () {
    std :: queue<int> q;
    q.push(0);
    inq[0] = true;
    while (!q.empty()) {
	int x = q.front(); q.pop();
	for (int i = head[x]; i; i = nxt[i]) {
	    if (d[to[i]] < d[x] + dis[i]) {
		d[to[i]] = d[x] + dis[i];
		if (!inq[to[i]]) {
		    if (++cir[to[i]] >= N) return false;
		    q.push(to[i]), inq[to[i]] = true;
		}
	    }
	}
	inq[x] = false;
    }
    return true;
}

void add_edge (int u, int v, int w) {
    nxt[++tmp] = head[u];
    head[u] = tmp;
    to[tmp] = v;
    dis[tmp] = w;
}
