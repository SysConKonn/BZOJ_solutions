#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#define MAX_N 2000020
#define MAX_X 1300
#define INF 214748364
using namespace std;
struct Edge {
  int from, to, dist;
  Edge(int u, int v, int w) : from(u), to(v), dist(w) {}
};

struct HeadNode {
  int d, u;
  bool operator < (const HeadNode& rhs) const {
    return d > rhs.d;
  }
};

struct Dijkstra {
  int n, m; // point num:n, edge num: m
  vector<Edge> edges; // the detail information
  vector<int> G[MAX_N]; // the serial number number of every edge
  bool done[MAX_N];
  int d[MAX_N]; // every distance from u

  void init (int n) {
    this->n = n;
    for (register int i = 0;i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge (int from, int to, int dist) {
    //printf("%d %d %d\n", from, to, dist);
    edges.push_back(Edge(from, to, dist));
    edges.push_back(Edge(to, from, dist));
    int ml = edges.size();
    G[from].push_back(ml - 2);
    G[to].push_back(ml -1);
    return;
  }
  
  int find (int s) {
    priority_queue<HeadNode> Q;
    for(register int i = 0;i < n; i++) d[i] = INF;
    d[s] = 0;
    memset(done, 0, sizeof(done));
    Q.push((HeadNode){0, s});

    while (!Q.empty()) {
      HeadNode x = Q.top();Q.pop();
      int u = x.u;
      if(done[u]) continue;
      done[u] = true;
      for(register int i = 0;i < G[u].size(); i++) {
	       Edge& e = edges[G[u][i]];
	       //if(tl > t[e.from] || tl > t[e.to]) continue;
	       if(d[e.to] > d[u] + e.dist) {
	       d[e.to] = d[u] + e.dist;
      	  Q.push((HeadNode){d[e.to], e.to});
	       }
      }
    }
    return d[n - 1];
  }
}p;

int solve() {
  return p.find(0);
}

void solve2 (int N, int M) {
  int min_ = INF;
  if (M > N) swap(N, M);
  int d;
  for (register int i = 1;i <= N; ++i) {scanf("%d", &d);min_ = min_ > d ? d : min_;}
  printf("%d\n", min_);
  return;
}

int matr[MAX_X][MAX_X], N, M;
void Read() {
  int d;
  int t = p.n - 1;
  for (register int i = 1;i < M; ++i) {
      scanf("%d", &d);
      p.AddEdge(matr[1][i] * 2, 0, d);
      p.AddEdge(0, matr[1][i] * 2, d);
  }
  for (register int i = 2;i < N; ++i) {
    for (int j = 1;j < M; ++j) {
      scanf("%d", &d);
      int x = matr[i][j];
      p.AddEdge(x * 2, (x - M) * 2 + 1, d);
      p.AddEdge((x - M) * 2 + 1, x * 2, d);
    }
  }
  for (register int i = 1;i < M; ++i) {
    scanf("%d", &d);
    p.AddEdge(matr[N - 1][i] * 2 - 1, t, d);
    p.AddEdge(t, matr[N - 1][i] * 2 - 1, d);
  }
  
  for (register int i = 1;i < N; ++i) {
    scanf("%d", &d);
    p.AddEdge(matr[i][1] * 2 - 1, t, d);
    p.AddEdge(t, matr[i][1] * 2 - 1, d);
    for (register int j = 2;j < M; ++j) {
      scanf("%d", &d);
      int x = matr[i][j] * 2 - 1;
      p.AddEdge(x, x - 1, d);
      p.AddEdge(x - 1, x, d);
    }
    scanf("%d", &d);
    p.AddEdge(matr[i][M - 1] * 2, 0, d);
    p.AddEdge(0, matr[i][M - 1] * 2, d);
  }
  
  for (register int i = 1;i < N; ++i) {
    for (register int j = 1;j < M; ++j) {
      int x = matr[i][j] * 2 - 1;
      scanf("%d", &d);
      p.AddEdge(x, x + 1, d);
      p.AddEdge(x + 1, x, d);
    }
  }
}

int main () {
  scanf("%d%d", &N, &M);
  if (N == 1 || M == 1) {solve2(N, M);return 0;}
  N--, M--;
  p.n = N * M * 2 + 2;
  N++, M++;
  int sum = 1;
  for (register int i = 1;i < N; ++i)
    for (register int j = 1;j < M; ++j)
      matr[i][j] = sum++;
  Read();
  
  printf("%d\n", solve());
  return 0;
}
