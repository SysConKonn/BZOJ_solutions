#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#define MAX_N 2007
#define MAX_M 100007
#define INF 2147483647

int N, M;
int head[MAX_N], to[MAX_M], nxt[MAX_M], flow[MAX_M], cap = 1;
int a[MAX_N], tmp[MAX_N], dep[MAX_N];
int S, T;
int res[MAX_N][MAX_N];
bool vis[MAX_N];
std::queue<int> q;

void add_edge (int u, int v, int w) {
    nxt[++cap] = head[u];
    head[u] = cap;
    to[cap] = v;
    flow[cap] = w;
}

bool bfs () {
    memset(dep, 0, sizeof(dep));
    q.push(S);
    dep[S] = 1;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = head[x]; i; i = nxt[i]) {
            if (dep[to[i]] || flow[i] <= 0) continue;
            dep[to[i]] = dep[x] + 1;
            q.push(to[i]);
        }
    }
    return dep[T];
}

int dfs (int x, int f) {
    if (x == T) return f;
    int w, used = 0;
    for (int i = head[x]; i; i = nxt[i]) {
        if (dep[to[i]] != dep[x] + 1) continue;
        w = dfs(to[i], std::min(flow[i], f - used));
        flow[i] -= w; flow[i ^ 1] += w;
        used += w;
        if (used == f) return f;
    }
    if (used == 0) dep[x] = 0;
    return used;
}

void dfs2 (int x) {
    vis[x] = true;
    for (int i = head[x]; i; i = nxt[i]) 
        if (flow[i] && !vis[to[i]])
            dfs2 (to[i]);
}

void restore () {
    for (int i = 2;i <= cap; i += 2)
        flow[i] = flow[i + 1] = (flow[i] + flow[i + 1]) / 2;
}

void solve (int l, int r) {
    if (l == r) return;
    S = a[l], T = a[r];
    restore (); 
    int f = 0;
    while (bfs()) f += dfs(S, INF); 
    memset(vis, false, sizeof(vis));
    dfs2 (S);
    //printf("%d %d %d %d %d\n", S, T, f, l, r);
    for (int i = 1;i <= N; ++i) if (vis[i])
        for (int j = 1;j <= N; ++j) if (!vis[j])
            res[i][j] = res[j][i] = std::min(res[i][j], f);
    int L = l, R = r;
    for (int i = l;i <= r; ++i) 
        if (vis[a[i]]) tmp[L++] = a[i];
        else tmp[R--] = a[i];
    // for (int i = l;i <= r; ++i) printf("%d ", vis[i]); puts("");
    // for (int i = l;i <= r; ++i) printf("%d ", tmp[i]); puts("");
    for (int i = l;i <= r; ++i) a[i] = tmp[i];
    solve (l, L - 1), solve(R + 1, r);
}

void init () {
    memset(head, 0, sizeof(head));
    memset(to, 0, sizeof(to));
    memset(nxt, 0, sizeof(nxt));
    memset(flow, 0, sizeof(flow));
    memset(res, 127, sizeof(res));
}

int main () {
    int t, q;
    scanf("%d", &t);
    while (t--) {
        init ();
        scanf("%d%d", &N, &M);
        int u, v, w;
        for (int i = 1;i <= M; ++i) 
            scanf("%d%d%d", &u, &v, &w), add_edge (u, v, w), add_edge (v, u, w);

        for (int i = 1;i <= N; ++i) a[i] = i; 
        solve(1, N);            
        scanf("%d", &q);
        int ans = 0;/* 
        for (int i = 1;i <= N; ++i) {
            for (int j = i + 1;j <= N; ++j) printf("%d ", res[i][j]); puts("");
        } */
        while (q--) {
            ans = 0;
            scanf("%d", &w);
            for (int i = 1;i <= N; ++i) 
                for (int j = i + 1;j <= N; ++j) if (res[i][j] <= w) ans++;
            printf("%d\n", ans);
        } puts("");
    }
    return 0;
}