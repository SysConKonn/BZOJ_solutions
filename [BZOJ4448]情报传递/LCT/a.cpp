#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define MAX_N 3000007
 
int N, Q;
int col[MAX_N];
int res[MAX_N], ans[MAX_N];
 
struct ques {
    int u, v, id;
};
 
std::vector<ques> qry[MAX_N];
 
namespace lct {
    int c[MAX_N][2], fa[MAX_N];
    int sum[MAX_N], s[MAX_N], w[MAX_N], wum[MAX_N];
    int q[MAX_N], top;
    bool rev[MAX_N];
 
    void pushdown (int x) {
        if (rev[x]) {
            int ls = c[x][0], rs = c[x][1];
            rev[x] ^= 1, rev[ls] ^= 1, rev[rs] ^= 1;
            std::swap(c[x][0], c[x][1]);
        }
    }
 
    void update (int x) {
        int ls = c[x][0], rs = c[x][1];
        sum[x] = s[x] + sum[ls] + sum[rs];
        wum[x] = w[x] + wum[ls] + wum[rs];
    }
 
    inline bool isroot (int x) {return c[fa[x]][0] != x && c[fa[x]][1] != x;}
 
    void rotate (int &x) {
        int y = fa[x], z = fa[y], l, r;
        l = c[y][1] == x, r = l ^ 1;
        if (!isroot (y)) 
            c[z][c[z][1] == y] = x;
        fa[x] = z, fa[y] = x, fa[c[x][r]] = y;
        c[y][l] = c[x][r], c[x][r] = y;
        update (y), update (x);
    }
 
    void splay (int &x) {
        top = 0; q[++top] = x;
        for (int i = x; !isroot(i); i = fa[i]) q[++top] = fa[i];
        for (int i = top; i; --i) pushdown(q[i]);
        while (!isroot (x)) {
            int y = fa[x], z = fa[y];
            if (!isroot(y))
                if (c[y][1] == x ^ c[z][1] == y) rotate (x);
                else rotate (y);
            rotate (x);
        }
    }
 
    void access (int x) {
        for (int t = 0; x; t = x, x = fa[x])
            splay(x), c[x][1] = t, update(x);
    }
 
    void makeroot (int x) {
        access(x), splay(x), rev[x] ^= 1;
    }
 
    void link (int x, int f) {
        makeroot(x);
        fa[x] = f;
    }
 
    void cut (int x, int y) {
        makeroot(x);
        access(y), splay(y);
        c[y][0] = fa[x] = 0;
    }
 
    int query (int x, int y, int op) { 
        makeroot (x);
        access(y), splay(y);
        return op == 1 ? wum[y] : sum[y];
    }
};
 
int main () {
    scanf("%d", &N);
    for (int i = 1;i <= N; ++i) lct::w[i] = 1;
    int f;
    for (int i = 1;i <= N; ++i) {
        scanf("%d", &f);
        if (f != 0) lct::link(i, f);
    } 
    scanf("%d", &Q);
    int op, k = 0;
    int u, v, c;
    for (int i = 1;i <= Q; ++i) {
        scanf("%d", &op);
        if (op == 2) scanf("%d", &u), col[i] = u;
        else {
            scanf("%d%d%d", &u, &v, &c);
            k++;
            ans[k] = lct::query(u, v, 1);
            if (i - c - 1 > 0) qry[i - c - 1].push_back((ques){u, v, k});
        }
    } 
    for (int i = 1;i <= Q; ++i) {
        if (col[i]) lct::s[col[i]] = 1, lct::splay(col[i]);
        int m = qry[i].size();
        for (int j = 0;j < m; ++j) {
            int u = qry[i][j].u, v = qry[i][j].v, id = qry[i][j].id;
            res[id] = lct::query(u, v, 0);
        }
    }
    for (int i = 1;i <= k; ++i) printf("%d %d\n", ans[i], res[i]);
    return 0;
}
