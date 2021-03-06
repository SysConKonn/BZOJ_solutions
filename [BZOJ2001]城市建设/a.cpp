#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 20007
#define MAX_M 50007
#define MAX_L 20
#define INF 1e9
typedef long long ll;

int N, M, Q;
int fa[MAX_N];
int map[MAX_M];
ll dis[MAX_M], res[MAX_M];

struct edge {
    int u, v, id;
    ll w;
}e[MAX_L][MAX_M], d[MAX_M], t[MAX_M];

struct query {
    int id;
    ll w;
}qry[MAX_M];

int find (int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}

inline void reset (int tot, edge* a) {
    for (int i = 1;i <= tot; ++i)
        fa[a[i].u] = a[i].u, fa[a[i].v] = a[i].v;
}

inline bool cmp (const edge a, const edge b) {return a.w < b.w;}

inline ll con (int& tot) {
    int tmp = 0;
    std::sort(d + 1, d + tot + 1, cmp);
    // for (int i = 1;i <= tot; ++i) printf("%d %d %lld\n", d[i].u, d[i].v, d[i].w);

    for (int i = 1;i <= tot; ++i) {
        int q = find(d[i].u), p = find(d[i].v);
        if (p == q) continue;
        fa[p] = q;
        t[++tmp] = d[i];
    }

    reset(tmp, t);
    ll sum = 0;
    for (int i = 1;i <= tmp; ++i) {
        int q = find(t[i].u), p = find(t[i].v);
        if (p == q || t[i].w == -INF) continue;
        fa[p] = q;
        sum += t[i].w;
    }

    tmp = 0;
    for (int i = 1;i <= tot; ++i) {
        int q = find(d[i].u), p = find(d[i].v);
        if (p == q) continue;
        t[++tmp] = d[i];
        t[tmp].u = q;
        t[tmp].v = p;
        map[d[i].id] = tmp;
    }

    reset (tot, d);
    tot = tmp;
    for (int i = 1;i <= tot; ++i)
        d[i] = t[i];
    // for (int i = 1;i <= tot; ++i) printf("%d %d %lld\n", d[i].u, d[i].v, d[i].w);
    return sum;
}

void reduce (int& tot) {
    int tmp = 0;
    std::sort(d + 1, d + tot + 1, cmp);
    for (int i = 1;i <= tot; ++i) {
        int p = find(d[i].u), q = find(d[i].v);
        if (p != q) {
            fa[p] = q;
            t[++tmp] = d[i];
            map[d[i].id] = tmp;
        } else if (d[i].w == INF) {
            t[++tmp] = d[i];
            map[d[i].id] = tmp;
        }
    }
    reset(tot, d);
    tot = tmp;
    for (int i = 1;i <= tmp; ++i) d[i] = t[i];
}

void solve (int l, int r, int lev, int end, ll sum) {
    // printf("%d %d %d %d %d\n", l, r, lev, end, sum);
    if (l == r) dis[qry[l].id] = qry[l].w;
    for (int i = 1;i <= end; ++i) {
        e[lev][i].w = dis[e[lev][i].id];
        d[i] = e[lev][i];
        map[e[lev][i].id] = i;
    }
    // for (int i = 1;i <= end; ++i) printf("%d %d %lld\n", e[lev][i].u, e[lev][i].v, e[lev][i].w);
    int p, q;
    if (l == r) {
        res[l] = sum;
        std::sort (d + 1, d + end + 1, cmp);
        for (int i = 1;i <= end; ++i) {
            p = find(d[i].u), q = find(d[i].v);
            if (p == q) continue;
            fa[p] = q;
            res[l] += d[i].w;
        }
        reset(end, d);
        return;
    }

    for (int i = l;i <= r; ++i)
        d[map[qry[i].id]].w = -INF;
    sum += con(end);

    for (int i = l;i <= r; ++i)
        d[map[qry[i].id]].w = INF;
    reduce(end);

    for (int i = 1;i <= end; ++i)
        e[lev + 1][i] = d[i];

    int mid = l + r >> 1;
    solve(l, mid, lev + 1, end, sum);
    solve(mid + 1, r, lev + 1, end, sum);
}

int main () {
    scanf("%d%d%d", &N, &M, &Q);
    for (int i = 1;i <= M; ++i)
        scanf("%d%d%lld", &e[0][i].u, &e[0][i].v, &e[0][i].w), dis[i] = e[0][i].w, e[0][i].id = i;
    for (int i = 1;i <= N; ++i) fa[i] = i;
    for (int i = 1;i <= Q; ++i)
        scanf("%d%lld", &qry[i].id, &qry[i].w);
    solve(1, Q, 0, M, 0LL);
    for (int i = 1;i <= Q; ++i) printf("%lld\n", res[i]);
    return 0;
}
