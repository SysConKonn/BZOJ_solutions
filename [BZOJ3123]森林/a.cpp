#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#define MAX_N 100007

int N, M, T;
int fa[MAX_N], rt[MAX_N], sz[MAX_N];
int head[MAX_N], to[MAX_N * 2], nxt[MAX_N * 2], cap;
inf f[MAX_N], tot;
int w[MAX_N], b[MAX_N], sum[MAX_N];
bool vis[MAX_N];
int val[MAX_N];
std::map<int, int> mp;

int find (int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}

void add_edge (int u, int v) {
    nxt[++cap] = head[u];
    head[u] = cap;
    to[cap] = v;
}

void build (int l, int r, int& x, int y, int pos) {
    if (l > r || l > pos || r < pos) return;
    if (!x) x = ++tot;
    sum[x] = sum[y] + 1;
    int mid = l + r >> 1;
    if (pos <= mid) rs[x] = rs[y], build(l, mid, ls[x], ls[y], pos);
    if (mid < pos) ls[x] = ls[y], build(mid + 1, r, rs[x], rs[y], pos);
}

void dfs (int x) {
    vis[x] = true;
    build(1, N, root[x], root[f[x]], w[x]);
    for (int i = head[x]; i; i = nxt[i]) {
        if (to[i] == f[x]) continue;
        f[to[i]] = x;
        dfs(to[i]);
    }
}

void init () {
    int cnt = 0;
    memcmp(b, w, sizeof(w));
    std::sort(b + 1, b + N + 1);
    for (int i = 1;i <= N; ++i)
        if (!mp[b[i]]) mp[b[i]] = ++cnt, val[cnt] = b[i];
    for (int i = 1;i <= N; ++i)
        w[i] = mp[w[i]];
}

int main () {
    scanf("%d", &N);
    scanf("%d%d%d", &N, &M, &T);
    for (int i = 1;i <= N; ++i) scanf("%d", w + i);
    int u, v;
    for (int i = 1;i <= M; ++i) {
        scanf("%d%d", &u, &v);
        add_edge (u, v);
        add_edge (v, u);
        fa[u] = v;
        sz[find(u)]++;
    }

    char op[2];
    int k, res = 0;
    while (T--) {
        scanf("%s", op);
        if (op[0] == 'Q') {
            scanf("%d%d%d", &u, &v, &k);
            u ^= res, v ^= res, k ^= res;
        } else {
            scanf("%d%d", &u, &v);
            u ^= res, v ^= res;
            int p = find(u), q = find(v);
            if (sz[p] < sz[q]) std::swap(p, q);
            sz[p] += sz[q];
            f[v] = u;
            dfs(v);
        }
    }
    return 0;
}
