#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>
#define MAX_N 2000050
#define INF 2147483647
using namespace std;

struct heapnode {
    int d, u;
    bool operator < (const heapnode& rhs) const {
	return d > rhs.d;
    }
};

int head[MAX_N], to[MAX_N * 3], nxt[MAX_N * 3], dis[MAX_N * 3], top;
int matr[1010][1010];
int N, M, s, t;
int d[MAX_N];

void AddEdge (int u, int v, int w) {
    //printf("%d %d %d\n", u, v, w);
    nxt[++top] = head[u];
    head[u] = top;
    to[top] = v;
    dis[top] = w;
}

void Read() {
    int d;
    for (register int i = 1;i < M; ++i) {
	scanf("%d", &d);
    	AddEdge(matr[1][i] * 2, 0, d);
    	AddEdge(0, matr[1][i] * 2, d);
    }
    for (register int i = 2;i < N; ++i) {
	for (int j = 1;j < M; ++j) {
	    scanf("%d", &d);
	    int x = matr[i][j];
	    AddEdge(x * 2, (x - M) * 2 + 1, d);
	    AddEdge((x - M) * 2 + 1, x * 2, d);
    	}
    }
    for (register int i = 1;i < M; ++i) {
	scanf("%d", &d);
	AddEdge(matr[N - 1][i] * 2 - 1, t, d);
	AddEdge(t, matr[N - 1][i] * 2 - 1, d);
    }
	  
    for (register int i = 1;i < N; ++i) {
	scanf("%d", &d);
	AddEdge(matr[i][1] * 2 - 1, t, d);
    	AddEdge(t, matr[i][1] * 2 - 1, d);
    	for (register int j = 2;j < M; ++j) {
	    scanf("%d", &d);
	    int x = matr[i][j] * 2 - 1;
	    AddEdge(x, x - 1, d);
	    AddEdge(x - 1, x, d);
	}
    	scanf("%d", &d);
    	AddEdge(matr[i][M - 1] * 2, 0, d);
    	AddEdge(0, matr[i][M - 1] * 2, d);
    }
  
    for (register int i = 1;i < N; ++i) {
	for (register int j = 1;j < M; ++j) {
	    int x = matr[i][j] * 2 - 1;
	    scanf("%d", &d);
	    AddEdge(x, x + 1, d);
	    AddEdge(x + 1, x, d);
    	}
    }
}

void solve2 (int N, int M) {
    int min_ = INF;
    if (M > N) swap(N, M);
    int d;
    for (register int i = 1;i <= N; ++i) {scanf("%d", &d);min_ = min_ > d ? d : min_;}
    printf("%d\n", min_);
    return;
}

void init() {
    memset(head, 0, sizeof(head));
    memset(to, 0, sizeof(to));
    memset(nxt, 0, sizeof(nxt));
    memset(dis, 0, sizeof(dis));
}

int done[MAX_N];

void find(int s, int t) {
    priority_queue<heapnode> Q;
    for (register int i = 0;i <= t + 1; ++i) d[i] = INF;
    d[s] = 0;
    memset(done, 0, sizeof(done));
    Q.push((heapnode){0, s});

    while (!Q.empty()) {
	heapnode x = Q.top(); Q.pop();
	int u = x.u;
	if (done[u]) continue;
	done[u] = true;
	for (register int i = head[u]; i; i = nxt[i]) {
	    int d_ = dis[i], v = to[i];
	    if (d[v] > d[u] + d_) {
		d[v] = d[u] + d_;
		Q.push((heapnode){d[v], v});
	    }
	}
    }
    printf("%d\n", d[t]);
}

int main () {
    scanf("%d%d", &N, &M);
    if (N == 1 || M == 1) {solve2(N, M);return 0;}
    s = 0, t = (N - 1) * (M - 1) * 2 + 1;

    int sum = 1;
    for (register int i = 1;i < N; ++i)
	for (register int j = 1;j < M; ++j)
	    matr[i][j] = sum++;
    init();
    Read();
    find(s, t);
    return 0;
}
