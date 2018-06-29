#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 100007
#define MAX_M 200007

int N, M;
int pa[MAX_N], res;

struct edge {
    int u, v, a, b;
    bool operator < (const edge& rhs) const {
        return a < rhs.a;
    }
}e[MAX_M];

namespace lct {
    int val[MAX_M], mx[MAX_M];
    int c[MAX_M][2], fa[MAX_M];
    int q[MAX_M], top;
    bool rev[MAX_M];

    inline void update (int x) {
        int ls = c[x][0], rs = c[x][1];
        mx[x] = x;
        if (val[mx[ls]] > val[mx[x]]) mx[x] = mx[ls];
        if (val[mx[rs]] > val[mx[x]]) mx[x] = mx[rs];
    }

    inline void pushdown (int x) {
        int ls = c[x][0], rs = c[x][1];
        if (rev[x]) {
            rev[x] ^= 1, rev[ls] ^= 1, rev[rs] ^= 1;
            std::swap(c[x][0], c[x][1]);
        }
    }

    inline bool isroot (int x) {return c[fa[x]][0] != x && c[fa[x]][1] != x;}

    inline void rotate (int &x) {
        int y = fa[x], z = fa[y], l, r;
        l = c[y][1] == x, r = l ^ 1;
        if (!isroot(y))
            c[z][c[z][1] == y] = x;
        fa[x] = z, fa[y] = x, fa[c[x][r]] = y;
        c[y][l] = c[x][r], c[x][r] = y;
        update(y), update(x);
    }

    inline void splay (int &x) {
        top = 0;q[++top] = x;
        for (int i = x; !isroot(i); i = fa[i]) q[++top] = fa[i];
        for (int i = top; i; --i) pushdown(q[i]);
        while (!isroot(x)) {
            int y = fa[x], z = fa[y];
            if (!isroot(y))
                if (c[z][0] == y ^ c[y][0] == x) rotate (x);
                else rotate (y);
            rotate (x);
        }
    }

    inline void access (int x) {
        for (int t = 0; x; t = x, x = fa[x])
            splay(x), c[x][1] = t, update(x);
    }

    inline void makeroot (int x) {
        access(x), splay(x);
        rev[x] ^= 1;
    }

    inline void link (int x, int f) {
        makeroot(x);
        fa[x] = f;
    }

    inline void cut (int x, int y) {
        makeroot(x), access(y), splay(y);
        fa[x] = c[y][0] = 0;
        update(y);
    }

    inline int query (int x, int y) {
        makeroot(x), access(y), splay(y);
        return mx[y];
    }
};

using namespace lct;

int find (int x) {return pa[x] == x ? x : pa[x] = find(pa[x]);}

int main () {
    scanf("%d%d", &N, &M);
    // int u, v, a, b;
    for (int i = 1;i <= M; ++i) 
        scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].a, &e[i].b);
    for (int i = 1;i <= N; ++i) pa[i] = i;
    std::sort(e + 1, e + M + 1);
    // for (int i = 1;i <= M; ++i) printf("%d %d %d %d\n", e[i].u, e[i].v, e[i].a, e[i].b); 
    int res = 1e9;
    for (int i = 1;i <= M; ++i) {
        int u = e[i].u, v = e[i].v, a = e[i].a, b = e[i].b;
        if (find(u) == find(v)) {
            int t = query(u, v);
            if (val[t] > b) {
                cut(t, e[t - N].u);
                cut(t, e[t - N].v);
            } else {
                if (find(1) == find(N))
                    res = std::min(res, a + val[query(1, N)]);
                continue;
            }
        } else pa[find(u)] = find(v);
        val[N + i] = b; mx[N + i] = N + i;
        link(u, N + i);
        link(v, N + i);
        if (find(1) == find(N)) res = std::min(res, a + val[query(1, N)]);
    }
    printf("%d\n", res == 1e9 ? -1 : res);
    return 0;
}
