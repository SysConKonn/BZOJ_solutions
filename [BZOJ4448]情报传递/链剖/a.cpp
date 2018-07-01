#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define MAX_N 2000007
 
struct ques {
    int u, v, id;
};

int N, Q;
int head[MAX_N], to[MAX_N * 2], nxt[MAX_N * 2], cap;
int fa[MAX_N], dep[MAX_N], sz[MAX_N], top[MAX_N], idx[MAX_N], cnt;
int col[MAX_N];
int sum[MAX_N], res[MAX_N], ans[MAX_N];
bool colored[MAX_N];
std::vector<ques> qry[MAX_N];
 
void add_edge (int u, int v) {
    nxt[++cap] = head[u];
    head[u] = cap;
    to[cap] = v;
}
 
void get_dep (int x) {
    sz[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        if (to[i] == fa[x]) continue;
        fa[to[i]] = x, dep[to[i]] = dep[x] + 1;
        get_dep(to[i]);
        sz[x] += sz[to[i]];
    }
}
 
void get_top (int x, int tp) {
    idx[x] = ++cnt;
    top[x] = tp;
    int k = 0;
    for (int i = head[x]; i; i = nxt[i]) 
        if (to[i] != fa[x] && sz[to[i]] > sz[k]) k = to[i];
    if (k == 0) return;
    get_top(k, tp);
    for (int i = head[x]; i; i = nxt[i])
        if (to[i] != fa[x] && to[i] != k) 
            get_top(to[i], to[i]);
}
 
void add (int x, int l, int r, int pos) {
    if (l > r || l > pos || r < pos) return;
    sum[x]++;
    if (l == r) return;
    int mid = l + r >> 1;
    if (pos <= mid) add(x * 2, l, mid, pos);
    if (pos > mid) add(x * 2 + 1, mid + 1, r, pos);
}
 
inline int get_lca (int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]]) u = fa[top[u]];
        else v = fa[top[v]];
    }
    return dep[v] > dep[u] ? u : v;
}
 
int query (int x, int l, int r, int totl, int totr) {
    if (l > r || l > totr || r < totl) return 0;
    if (totl <= l && r <= totr) return sum[x];
    int mid = l + r >> 1, ans = 0;
    if (totl <= mid) ans += query (x * 2, l, mid, totl, totr);
    if (totr > mid) ans += query (x * 2 + 1, mid + 1, r, totl, totr);
    return ans;
}
 
void update (int u, int v, int id) {
    // if (u == v) return;
    while (1) {
        int t = top[u];
        if (dep[v] >= dep[t]) t = v;
        res[id] += query (1, 1, N, std::min(idx[t], idx[u]), std::max(idx[t], idx[u]));
        // ans[id] += idx[u] - idx[t] + 1;
        if (dep[top[u]] <= dep[v]) break;
        u = fa[top[u]];
        if (dep[u] < dep[v]) break;
    }
}
 
int main () {
    scanf("%d", &N);
    for (int i = 1;i <= N; ++i) {
        scanf("%d", fa + i);
        if (fa[i] != 0) add_edge (i, fa[i]), add_edge (fa[i], i);
    }
    memset(fa, 0, sizeof(fa));
    dep[1] = 1;
    get_dep (1);
    get_top (1, 1);
    scanf("%d", &Q);
    int op;
    int u, v, c, k = 0;
    for (int i = 1;i <= Q; ++i) {
        scanf("%d", &op);
        if (op == 2) scanf("%d", &u), col[i] = u;
        else {
            scanf("%d%d%d", &u, &v, &c);
            k++;
            // if (i - c - 1 <= 0) {
            //     int lca = get_lca (u, v);
            //     update (u, lca, k);
            //     update (v, lca, k);
            // } else 
            ans[k] = dep[u] + dep[v] - 2 * dep[get_lca (u, v)] + 1;
            if (i - c - 1 > 0)
                qry[i - c - 1].push_back((ques){u, v, k});
        }
    }
    for (int i = 1;i <= Q; ++i) {
        if (col[i]) add(1, 1, N, idx[col[i]]), colored[col[i]] = true;
        if (qry[i].size() == 0) continue;
        int m = qry[i].size();
        for (int j = 0;j < m; ++j) {
            int u = qry[i][j].u, v = qry[i][j].v, id = qry[i][j].id;
            int lca = get_lca (u, v);
            update(u, lca, id);
            update(v, lca, id);
            if (colored[lca]) res[id]--;
        }
    }
    for (int i = 1;i <= k; ++i) printf("%d %d\n", ans[i], res[i]);
    return 0;
}
