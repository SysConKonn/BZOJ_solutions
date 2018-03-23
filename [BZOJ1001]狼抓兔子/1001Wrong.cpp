#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define MAX_N 1001
#define INF 1000000001
using namespace std;
struct Edge {
  int from, to, cap, flow;
  Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
};
vector<Edge> edges;
vector <int> G[MAX_N];
int N, M, V, s, t;
int matr[MAX_N][MAX_N];
int cur[MAX_N], d[MAX_N];
bool vis[MAX_N];

void add_edge (int u, int v, int cap) {
  //printf("%d %d %d\n", u, v, cap);
  edges.push_back(Edge(u, v, cap, 0));
  edges.push_back(Edge(v, u, cap, 0));
  int m = edges.size();
  G[u].push_back(m - 2);
  G[v].push_back(m - 1);
}

bool BFS() {
  memset(vis, 0, sizeof(vis));
  queue<int> Q;
  //while (!Q.empty()) Q.pop();
  Q.push(s);
  d[s] = 0;
  vis[s] = 1;
  while (!Q.empty()) {
    int now = Q.front();
    Q.pop();
    for (int i = 0;i < G[now].size(); ++i) {
      Edge& e = edges[G[now][i]];
      if(!vis[e.to] && e.cap > e.flow) {
	vis[e.to] = 1;
	d[e.to] = d[now] + 1;
	Q.push(e.to);
      }
    }
  }
  return vis[t];
}

int DFS (int x, int a) {
  if(x == t || a == 0) return a;
  int flow = 0, f;
  for (int& i = cur[x]; i < G[x].size(); ++i) {
    Edge& e = edges[G[x][i]];
    if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
      e.flow += f;
      edges[G[x][i] ^ 1].flow -= f;
      flow += f;
      a -= f;
      if (a == 0) break;
    }
  }
  return flow;
}

int solve () {
  int flow = 0;
  while(BFS()) {
    memset(cur, 0, sizeof(cur));
    flow += DFS(s, INF);
    //printf("%d\n", flow);
  }
  return flow;
}
  
int main () {
  scanf("%d%d", &N, &M);
  V = N * M;
  int sum = 1;
  for (int i = 1;i <= N; ++i)
    for (int j = 1; j <= M; ++j)
      matr[i][j] = sum++;
  for (int i = 1;i <= N; ++i) {
    for (int j = 1;j <= M; ++j)
      printf("%d ", matr[i][j]);
    printf("\n");
  }
  for (int i = 1;i <= N; ++i) {
    for (int j = 1;j < M; ++j) {
      int d;
      scanf("%d", &d);
      add_edge(matr[i][j], matr[i][j + 1], d);
    }
  }
  //printf("\n");
  for (int i = 1;i < N; ++i) {
    for (int j = 1;j <= M; ++j) {
      int d;
      scanf("%d", &d);
      add_edge(matr[i][j], matr[i + 1][j], d);
    }
  }
  //printf("\n");
  for (int i = 1;i < N; ++i) {
    for (int j = 1;j < M; ++j) {
      int d;
      scanf("%d", &d);
      add_edge(matr[i][j], matr[i + 1][j + 1], d);
    }
  }

  printf("%d\n", solve());
  return 0;
}
