#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#define MAX_N 2007

int N;
int head[MAX_N], to[MAX_N * 2], nxt[MAX_N * 2], cap;
int dep[MAX_N], fa[MAX_N];
int res;
bool col[MAX_N];

struct node {
    int u, dep;
    bool operator < (const node& rhs) const {
        return dep < rhs.dep;
    }
};

void add_edge (int u, int v) {
    nxt[++cap] = head[u];
    head[u] = cap;
    to[cap] = v;
}

void dfs (int x) {
    for (int i = head[x]; i; i = nxt[i])
        if (to[i] != fa[x])
            fa[to[i]] = x, dep[to[i]] = dep[x] + 1, dfs(to[i]);
}

void dfs2 (int x, int f, int dep) {
    if (dep > 2) return;
    col[x] = true;
    for (int i = head[x]; i; i = nxt[i])
        if (to[i] != f) dfs2 (to[i], x, dep + 1);
}

void solve () {
    std::priority_queue<node> q; 
    for (int i = 1;i <= N; ++i) q.push((node){i, dep[i]});
    while (!q.empty()) {
        node x = q.top(); q.pop();
        if (col[x.u]) continue;
        int tmp = fa[fa[x.u]];
        dfs2 (tmp, 0, 0);
        res++;
    }
}

int main () {
    scanf("%d", &N);
    int v;
    for (int i = 2;i <= N; ++i) {
        scanf("%d", &v);
        add_edge(i, v), add_edge (v, i);
    }
    dfs(1);
    solve();
    printf("%d\n", res);
    return 0;
}
