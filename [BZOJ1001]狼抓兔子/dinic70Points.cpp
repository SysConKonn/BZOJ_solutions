#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define MAX_N 1200
#define INF 10000001
using namespace std;
struct Edge {
  int to, cap;
  Edge(int v, int d):to(v), cap(d) {}
};
vector <Edge> edges[MAX_N * MAX_N];

int N, M;
int s, t;
int dep[MAX_N * MAX_N], idep[MAX_N * MAX_N];
int matr[MAX_N][MAX_N];

void bfs (int s) {
  memset(dep, -1, sizeof(dep));
  memset(idep, 0, sizeof(idep));
  queue<int> Q;
  while (!Q.empty()) Q.pop();
  dep[s] = 0;
  idep[0]++;
  Q.push(s);
  while (!Q.empty()) {
    int now = Q.front();
    Q.pop();
    for (int i = 0;i < edges[now].size(); ++i) {
      Edge& e = edges[now][i];
      if(e.cap > 0 && dep[e.to] < 0) {
	dep[e.to] = dep[now] + 1;
	idep[dep[e.to]]++;
	Q.push(e.to);
      }
    }
  }
}

int find_ (int x, int u) {
  for (int i = 0;i < edges[u].size(); ++i)
    if(edges[u][i].to == x) return i;
}

int dfs (int now, int flow) {
  if(now == t) return flow;
  for(int i = 0;i < edges[now].size(); ++i) {
    Edge& e = edges[now][i];
    if((dep[e.to] == dep[now] + 1) && (e.cap > 0)) {
      int f = dfs(e.to, min(flow, e.cap));
      if(f > 0) {
	e.cap -= f;
	edges[e.to][find_(now, e.to)].cap += f;
	return f;
      }
    }
  }
  return 0;
}

void add_edge (int u, int v, int cap) {
  edges[u].push_back(Edge(v, cap));
  edges[v].push_back(Edge(u, cap));
}

int check () {
  bool book = false;
  int sum = 0;
  for (int i = 0;sum < N && i < N; ++i) {
    if(idep[i] == 0) book = true;
    sum += idep[i];
  }
  if (book == true) return 1;
  return 0;
}


int dinic () {

  int res = 0;
  int d = 0;
  for (;;) {
    bfs(s);
    if(dep[t] < 0) return res;
    while(d = dfs(s, INF)) res += d;
  }
  return res;
}

int main () {
  scanf("%d%d", &N, &M);
  s = 1, t = N * M;
  int sum = 1;
  memset(matr, 0, sizeof(matr));
  for (int i = 1;i <= N; ++i)
    for (int j = 1; j <= M; ++j)
      matr[i][j] = sum++;
  
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
  for (int i = 1;i < N; ++i) {
    for (int j = 1;j < M; ++j) {
      int d;
      scanf("%d", &d);
      add_edge(matr[i][j], matr[i + 1][j + 1], d);
    }
  }

  printf("%d\n", dinic());
  return 0;
}
