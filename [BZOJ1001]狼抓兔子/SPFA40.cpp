#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
typedef long long ll;
#define MAX_X 1000
#define MAX_N 2000010
#define INF 2147483647
using namespace std;
struct Edge {
	int from, to;
	int dist;
	Edge(int u, int v, int d) : from(u), to(v), dist(d) {}
};
vector <Edge> edges;
vector <int> G[MAX_N * 3];

int N, M, s, t;
int d[MAX_N];
bool vis[MAX_N];

void add_edge (int from, int to, int dist) {
	//printf("%d %d %d\n", from, to, dist);
	edges.push_back(Edge(from, to, dist));
	int m = edges.size();
	G[from].push_back(m - 1);
}

void Read(int s, int t) {
	int d;
	for (int i = 1;i <= N; ++i) {
		for (int j = 1;j < M; ++j) {
			scanf("%d", &d);
			int u, v;
			if (i == 1) u = s;
			else u = (i - 2) * (M - 1) * 2 + j * 2 - 1;
			if (i == N) v = t;
			else v = (i - 1) * (M - 1) * 2 + j * 2;
			add_edge(u, v, d);
			add_edge(v, u, d);
		}
	}
	for (int i = 1;i < N; ++i) {
		for (int j = 1;j <= M; ++j) {
			scanf("%d", &d);
			int u, v;
			if (j == 1) u = t;
			else u = (i - 1) * (M - 1) * 2 + j * 2 - 2;
			if (j == M) v = s;
			else v = (i - 1) * (M - 1) + j * 2 - 1;
			add_edge(u, v, d);
			add_edge(v, u, d);
		}
	}
	int top = 1;
	for (int i = 1;i < N; ++i) {
		for (int j = 1;j < M; ++j) {
			scanf("%d", &d);
			add_edge(top, top + 1, d);
			add_edge(top + 1, top, d);
			top += 2;
		}
	}
}

void spfa(int s, int t) {
	memset(vis, false, sizeof(vis));
	queue<int>Q;
	while (!Q.empty()) Q.pop();
	for (int i = 0;i <= t + 1; ++i) d[i] = INF;
	d[s] = 0;
	Q.push(s);
	vis[s] = true;
	while (!Q.empty()) {
		int x = Q.front(); Q.pop();
		for (int i = 0;i < G[x].size(); ++i) {
			Edge& e = edges[G[x][i]];
			if(d[e.to] > d[x] + e.dist) {
				d[e.to] = d[x] + e.dist;
				if (!vis[e.to]) {
					Q.push(e.to);
					vis[e.to] = true;
				}
			}
		}
		vis[x] = false;
	}
	printf("%d\n", d[t]);
}

int main () {
	scanf("%d%d", &N, &M);
	t = (N - 1) * (M - 1) * 2 + 1;
	Read(s, t);
	spfa(s, t);
	return 0;
}