#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define MAX_N 700010
#define INF 2147483647
using namespace std;

struct Edge {
  int from, to, cap, flow;
  Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
};
vector<Edge> edges;
vector<int> G[6 * MAX_N];
int N, M, V, s, t;
int cur[MAX_N], dep[MAX_N];

void add_edge (int from, int to, int cap) {
  edges.push_back(Edge(from, to, cap, 0));
  edges.push_back(Edge(to, from, cap, 0));
  int m = edges.size();
  G[from].push_back(m - 2);
  G[to].push_back(m - 1);
}

bool BFS() {
  memset(dep, 0, sizeof(dep));
  queue<int> Q;
  Q.push(s);
  dep[s] = 1;
  while (!Q.empty()) {
    int now = Q.front();
    Q.pop();
    if (now == t) return true;
    for (register int i = 0;i < G[now].size(); ++i) {
      Edge& e = edges[G[now][i]];
      //if (e.to == s) continue;
      if (dep[e.to] == 0 && e.cap > e.flow) {
	       dep[e.to] = dep[now] + 1;
	       if (e.to == t) return true;
	       Q.push(e.to);
      }
    }
  }
  return false;
}

int DFS(int x, int a) {
  if (x == t || a == 0) return a;
  int flow = 0, f;
  for (register int i = 0;i < G[x].size(); ++i) {
    Edge& e = edges[G[x][i]];
    if (e.cap > e.flow && dep[e.to] == dep[x] + 1) {
      int tmp = DFS(e.to, min(e.cap - e.flow, a - flow));
      e.flow += tmp;
      edges[G[x][i] ^ 1].flow -= tmp;
      flow += tmp;
      if (flow == a) return flow;
    }
  }
  if (!flow) dep[x] = -1;
  return flow;
}

int Max_Flow () {
  int flow = 0;
  while(BFS()) {
    flow += DFS(s, INF);
  }
  return flow;
}

void Read() {
  for (register int i = 0;i < N; ++i) 
    for (register int j = 1;j < M; ++j) {
      int d;
      scanf("%d", &d);
      add_edge(i * M + j, i * M + j + 1, d);
    }

  for (register int i = 0;i < N - 1; ++i)
    for (register int j = 1;j <= M; ++j) {
      int d;
      scanf("%d", &d);
      add_edge(i * M + j, (i + 1) * M + j, d);
    }

  for (register int i = 0;i < N - 1; ++i)
    for (register int j = 1;j < M; ++j) {
      int d;
      scanf("%d", &d);
      add_edge(i * M + j, (i + 1) * M + j + 1, d);
    }
}

void solve2 (int N, int M) {
  int min_ = INF;
  if (M > N) swap(N, M);
  int d;
  for (int i = 1;i <= N; ++i) {scanf("%d", &d);min_ = min_ > d ? d : min_;}
  printf("%d\n", min_);
  return;
}

int main () {
  scanf("%d%d", &N, &M);
  if (N == 1 || M == 1) {solve2(N, M); return 0;}
  V = N * M;
  s = 1, t = V;
  Read();
  printf("%d\n", Max_Flow());
  return 0;
}
