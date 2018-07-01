#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#define MAX_N 105007
typedef long long ll;
 
int N, M;
ll w[MAX_N], b[MAX_N];
int head[MAX_N], to[MAX_N * 4], nxt[MAX_N * 4], cap;
int fa[MAX_N], dep[MAX_N], sz[MAX_N], top[MAX_N];
ll st[MAX_N * 40];
int root[MAX_N], ls[MAX_N * 40], rs[MAX_N * 40], tot;
ll val[MAX_N];
std::map<ll, int> mp;
 
void add_edge (int u, int v) {
    nxt[++cap] = head[u];
    head[u] = cap;
    to[cap] = v;
}
 
void build (int l, int r, int& x, int y, int pos) {
    if (l > r || l > pos || r < pos) return;
    x = ++tot;
    st[x] = st[y] + 1;
    if (l == r) return;
    int mid = l + r >> 1;
    if (pos <= mid) rs[x] = rs[y], build (l, mid, ls[x], ls[y], pos);
    if (mid < pos) ls[x] = ls[y], build (mid + 1, r, rs[x], rs[y], pos);
}
 
void dfs (int x) {
    sz[x] = 1;
    build (1, N, root[x], root[fa[x]], w[x]);
    for (int i = head[x]; i; i = nxt[i]) {
        if (to[i] == fa[x]) continue;
        fa[to[i]] = x, dep[to[i]] = dep[x] + 1;
        dfs(to[i]);
        sz[x] += sz[to[i]];
    }
}
 
void get_top (int x, int tp) {
    top[x] = tp;
    int k = 0;
    for (int i = head[x]; i; i = nxt[i]) 
        if (to[i] != fa[x] && sz[to[i]] > sz[k]) k = to[i];
    if (k == 0) return;
    get_top (k, tp);
    for (int i = head[x]; i; i = nxt[i]) 
        if (to[i] != fa[x] && to[i] != k) 
            get_top (to[i], to[i]);
}
 
inline int get_lca (int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]]) u = fa[top[u]];
        else v = fa[top[v]];
    }
    return dep[v] > dep[u] ? u : v;
}
 
void init () {
    int cnt = 0;
    memcpy(b, w, sizeof(w));
    std::sort(b + 1, b + N + 1);
    for (int i = 1;i <= N; ++i) 
        if (!mp[b[i]]) 
            mp[b[i]] = ++cnt, val[cnt] = b[i];
    for (int i = 1;i <= N; ++i)
        w[i] = mp[w[i]];
}
 
int query (int l, int r, int a, int b, int c, int d, int k) {
    if (l > r) return 0;
    if (l == r) return l;
    int v = st[ls[a]] + st[ls[b]] - st[ls[c]] - st[ls[d]];
    int mid = l + r >> 1;
    if (k <= v) return query (l, mid, ls[a], ls[b], ls[c], ls[d], k);
    else return query (mid + 1, r, rs[a], rs[b], rs[c], rs[d], k - v);
}
 
int main () {
    scanf("%d%d", &N, &M);
    for (int i = 1;i <= N; ++i) scanf("%lld", w + i);
    init();
    int u, v;
    for (int i = 1;i < N; ++i) 
        scanf("%d%d", &u, &v), add_edge (u, v), add_edge (v, u);
    dfs(1); 
    get_top (1, 1);
    int k;
    ll res = 0;
    for (int i = 1;i <= M; ++i) {
        scanf("%d%d%d", &u, &v, &k);
        u ^= res;
        int lca = get_lca (u, v);
        // printf("%d %d %d\n", u, v, lca);
        res = val[query (1, N, root[u], root[v], root[fa[lca]], root[lca], k)];
        printf("%lld\n", res);
    }
    return 0;
}
