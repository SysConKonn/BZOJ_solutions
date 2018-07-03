#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 1000007
#define MAX_M 1000007

namespace lct {
    int c[MAX_M + MAX_N][2], fa[MAX_M + MAX_N];
    int q[MAX_M + MAX_N], top;
    int mx[MAX_N + MAX_M], val[MAX_N + MAX_M];
    bool rev[MAX_N];

    inline bool isroot (int x) {return c[fa[x]][0] != x && c[fa[x]][1] != x;}

    inline void pushdown (int x) {
        int ls = c[x][0], rs = c[x][1];
        if (rev[x]) {
            rev[x] ^= 1, rev[ls] ^= 1, rev[rs] ^= 1;
            std::swap(c[x][0], c[x][1]);
        }
    }

    inline void update (int x) {
        int ls = c[x][0], rs = c[x][1];
        mx[x] = x;
        if (val[mx[x]] < val[mx[ls]]) mx[x] = mx[ls];
        if (val[mx[x]] < val[mx[rs]]) mx[x] = mx[rs];
    }

    void rotate (int x) {
        int y = fa[x], z = fa[y], l, r;
        l = c[y][1] == x, r = l ^ 1;
        if (!isroot(y))
            c[z][c[z][1] == y] = x;
        fa[x] = z, fa[y] = x, fa[c[x][r]] = y;
        c[y][l] = c[x][r], c[x][r] = y;
        update (y), update (x);
    }

    void splay (int x) {
        top = 0, q[++top] = x;
        for (int i = x; !isroot(i); i = fa[i]) q[++top] = fa[i];
        for (int i =top; i; --i) pushdown(q[i]);
        while (!isroot(x)) {
            int y = fa[x], z = fa[y];
            if (!isroot(y))
                if (c[y][0] == x ^ c[z][0] == y) rotate (x);
                else rotate (y);
            rotate (x);
        }
    }

    inline void access (int x) {
        for (int t = 0; x; t = x, x = fa[x]) 
            splay(x), c[x][1] = t, update(x);
    }

    inline void makeroot (int x) {
        access(x), splay(x), rev[x] ^= 1;
    }

    inline void link (int x, int f) {
        makeroot(x), fa[x] = f;
    }

    inline void cut (int x, int y) {
        makeroot(x);
        access(y), splay(y);
        c[y][0] = fa[x] = 0;
    }

    inline int query (int x, int y) {
        makeroot(x);
        access(y), splay(y);
        return mx[y];
    }
};
using namespace lct;

int N, M, Q;
int f[MAX_N];

struct edge {
    int u, v, w, id;
    bool ditr;
}e[MAX_M];

struct ques {
    int u, v, tp, id, ans;
}qry[MAX_M];

int find (int x) {return x == f[x] ? x : f[x] = find(f[x]);} 

inline int get (int u, int v) {
    int l = 1, r = M, mid;
    while (l <= r) {
        mid = l + r >> 1;
        if (e[mid].u < u || (e[mid].u == u && e[mid].v < v)) l = mid + 1;
        else if (e[mid].u == u && e[mid].v == v) return mid;
        else r = mid - 1;
    }
}

inline bool cmp1 (const edge a, const edge b) {
    return a.w < b.w;
}

inline bool cmp2 (const edge a, const edge b) {
    return a.u == b.u ? a.v < b.v : a.u < b.u;
}

inline bool cmp3 (const edge a, const edge b) {
    return a.id < b.id;
}

int main () {
    scanf("%d%d%d", &N, &M, &Q);
    for (int i = 1;i <= M; ++i) {
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
        if (e[i].u > e[i].v) std::swap(e[i].u, e[i].v);
    }
    std::sort(e + 1, e + M + 1, cmp1);
    for (int i = 1;i <= M; ++i) {
        e[i].id = i;
        mx[N + i] = N + i;
        val[N + i] = e[i].w;
    }
    std::sort(e + 1, e + M + 1, cmp2);
    // for (int i = 1;i <= M; ++i) printf("%d %d\n", e[i].u, e[i].v);
    for (int i = 1;i <= Q; ++i) {
        scanf("%d%d%d", &qry[i].tp, &qry[i].u, &qry[i].v);
        if (qry[i].tp == 1) continue;
        if (qry[i].u > qry[i].v) std::swap(qry[i].u, qry[i].v);
        int idx = get (qry[i].u, qry[i].v);
        e[idx].ditr = true;
        qry[i].id = e[idx].id;
    }
    std::sort(e + 1, e + M + 1, cmp3);
    // for (int i = 1;i <= M; ++i) printf("%d %d\n", e[i].u, e[i].v);
    for (int i = 1;i <= N; ++i) f[i] = i;
    int cnt = 0;
    for (int i = 1;i <= M; ++i) {
        if (e[i].ditr) continue;
        int u = e[i].u, v = e[i].v;
        int p = find(u), q = find(v);
        // printf("%d %d %d %d\n", u, v, p, q);
        if (p == q) continue;
        f[p] = q;
        // printf("%d %d\n", u, v);
        link(u, N + i);
        link(v, N + i);
        cnt++;
        if (cnt == N - 1) break;
    }
    for (int i = Q; i; --i) {
        if (qry[i].tp == 1) qry[i].ans = val[query(qry[i].u, qry[i].v)];
        else {
            int u = qry[i].u, v = qry[i].v, idx = qry[i].id;
            int x = query(u, v);
            if (e[idx].w >= val[x]) continue;
            cut(e[x - N].u, x), cut(e[x - N].v, x);
            link(u, idx + N), link(v, idx + N);
        }
    }
    for (int i = 1;i <= Q; ++i) 
        if (qry[i].tp == 1) printf("%d\n", qry[i].ans);
    return 0;
}