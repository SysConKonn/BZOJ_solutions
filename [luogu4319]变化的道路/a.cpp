#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <stack>
#define MAX_N 50007
#define MAX_M 400007
#define R 32766

typedef long long ll;

namespace lct {
    int c[MAX_M * 2][3], fa[MAX_M * 2];
    int mx[MAX_M * 2];
    ll val[MAX_M * 2];
    int q[MAX_M * 2], top;
    bool rev[MAX_M * 2];

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

    inline void rotate (int x) {
        int y = fa[x], z = fa[y], l, r;
        l = (c[y][1] == x), r = l ^ 1;
        if (!isroot(y))
            c[z][c[z][1] == y] = x;
        fa[x] = z, fa[y] = x, fa[c[x][r]] = y;
        c[y][l] = c[x][r], c[x][r] = y;
        update(y), update(x);
    }

    inline void splay (int x) {
        top = 0, q[++top] = x;
        for (int i = x; !isroot(i); i = fa[i]) q[++top] = fa[i];
        for (int i = top; i; --i) pushdown(q[i]);
        while (!isroot(x)) {
            int y = fa[x], z = fa[y];
            if (!isroot(y))
                if ((c[y][0] == x) ^ (c[z][0] == y)) rotate (x);
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
        access(y); splay(y);
        return mx[y];
    }
};
using namespace lct;

int N, M;
ll ans, res[R + 100];

struct edge {
    int u, v, id;
    ll w;
}e[MAX_M * 2];

std::vector<int> tag[R * 6];

void modify (int x, int l, int r, int totl, int totr, int id) {
    if (l > r || l > totr || r < totl) return;
    if (totl <= l && r <= totr) {tag[x].push_back(id);return;}
    if (l == r) return;
    int mid = l + r >> 1;
    if (totl <= mid) modify (x * 2, l, mid, totl, totr, id);
    if (mid < totr) modify (x * 2 + 1, mid + 1, r, totl, totr, id);
}

void calc (int x, int l, int r) {
    std::stack<std::pair<int, int> > stk;
    int m = tag[x].size();
    for (int i = 0;i < m; ++i) {
        int id = tag[x][i], u = e[id - N - M].u, v = e[id - N - M].v, t = query(u, v);
        ll w = e[id - N - M].w;
        if (val[t] <= w) continue;
        stk.push(std::make_pair(t, 1));
        stk.push(std::make_pair(id, 0));
        cut(t, e[t - N - M].u), cut(t, e[t - N - M].v), ans -= e[t - N - M].w;
        link(id, e[id - N - M].u), link(id, e[id - N - M].v), ans += w;
    }
    if (l == r) res[l] = ans;
    else {
        int mid = l + r >> 1;
        calc(x * 2, l, mid), calc(x * 2 + 1, mid + 1, r);
    }
    while (!stk.empty()) {
        std::pair<int, int> p = stk.top(); stk.pop();
        int id = p.first;
        if (p.second == 0) cut(id, e[id - N - M].u), cut(id, e[id - N - M].v), ans -= e[id - N - M].w;
        else link(id, e[id - N - M].u), link(id, e[id - N - M].v), ans += e[id - N - M].w;
    }
}

int main () {
    scanf("%d", &N);
    for (int i = 1;i < N; ++i) {
        scanf("%d%d%lld", &e[i].u, &e[i].v, &e[i].w);
    }
    int l, r;
    scanf("%d", &M);
    for (int i = 1;i < N; ++i) {
        mx[N + M + i] = N + M + i;
        val[N + M + i] = e[i].w;
        ans += e[i].w;
        link(e[i].u, N + M + i);
        link(e[i].v, N + M + i);
    }
    for (int i = N;i < M + N; ++i) {
        scanf("%d%d%lld%d%d", &e[i].u, &e[i].v, &e[i].w, &l, &r);
        mx[N + M + i] = N + M + i;
        val[N + M + i] = e[i].w;
        modify (1, 1, R, l, r, N + M + i);
    }
    calc(1, 1, R);
    for (int i = 1;i <= R; ++i) printf("%lld\n", res[i] + 1);
    return 0;
}