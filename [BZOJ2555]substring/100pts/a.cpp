#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 3500007

char s[MAX_N];
int len;
int mask;

namespace lct {
    int w[MAX_N], tag[MAX_N];
    int fa[MAX_N], c[MAX_N][2];
    int q[MAX_N], top = 0;

    void add (int x, int val) {
        if (!x) return;
        w[x] += val;
        tag[x] += val;
    }

    void pushdown (int x) {
        if (!tag[x]) return;
        int ls = c[x][0], rs = c[x][1];
        add(ls, tag[x]), add(rs, tag[x]);
        tag[x] = 0;
    }

    inline bool isroot (int x) {return (c[fa[x]][0] != x) && (c[fa[x]][1] != x);}

    void rotate (int x) {
        int y = fa[x], z = fa[y], l, r;
        l = c[y][1] == x, r = l ^ 1;
        if (!isroot(y)) 
            c[z][c[z][1] == y] = x;
        fa[c[x][r]] = y, fa[y] = x, fa[x] = z;
        c[y][l] = c[x][r], c[x][r] = y;
    }

    void splay (int x) {
        top = 0; q[++top] = x;
        for (int i = x;!isroot(i); i = fa[i])
            q[++top] = fa[i];
        for (int i = top; i; --i)
            pushdown (q[i]);
        while (!isroot(x)) {
            int y = fa[x], z = fa[y];
            if (!isroot(y)) {
                if (c[z][0] == x ^ c[y][0] == x) rotate (x); 
                else rotate (y);
            }
            rotate (x);
        }
    }

    void access (int x) {
        for (int t = 0; x; t = x, x = fa[x])
            splay (x), c[x][1] = t;
    }

    void link (int x, int f) {
        fa[x] = f, access(f), splay(f), add(f, w[x]);
    }

    void cut (int x) {
        access(x), splay(x);
        add(c[x][0], -w[x]);
        fa[c[x][0]] = 0, c[x][0] = 0;
    }
}

namespace sam {
    int last = 1, sz = 1, root = 1;

    struct node {
        int fa, mx;
        int go[28];
        node () {}
        node (int mx_) : fa(0), mx(mx_) {
            memset(go, 0, sizeof(go));
        }
    }t[MAX_N];

    void insert (int c) {
        int p = last, np = ++sz;
        lct::w[np] = 1;
        t[np] = node(t[p].mx + 1);
        while (p && !t[p].go[c]) t[p].go[c] = np, p = t[p].fa;
        if (!p)
            t[np].fa = root, lct::link(np, root);
        else {
            int q = t[p].go[c];
            if (t[q].mx == t[p].mx + 1) {
                t[np].fa = q;
                lct::link(np, q);
            } else {
                int nq = ++sz;
                t[nq] = node(t[p].mx + 1);
                memcpy(t[nq].go, t[q].go, sizeof(t[q].go));
                t[nq].fa = t[q].fa;
                lct::link(nq, t[q].fa);
                t[q].fa = t[np].fa = nq;
                lct::cut(q);
                lct::link(q, nq), lct::link(np, nq);
                while (t[p].go[c] == q) 
                    t[p].go[c] = nq, p = t[p].fa;
            }
        }
        last = np;
    }

    void build () {
        len = strlen(s);
        for (int i = 0;i < len; ++i) insert(s[i] - 'A' + 1);
    }

    int query () {
        int p = root;
        len = strlen(s);
        for (int i = 0;i < len; ++i)
            if (!(p = t[p].go[s[i] - 'A' + 1])) return 0;
        lct::splay(p);
        mask ^= lct::w[p];
        return lct::w[p];
    }
};

void get (int m) {
    len = strlen(s);
    for (int i = 0;i < len; ++i) {
        m = (m * 131 + i) % len;
        std::swap(s[i], s[m]);
    }
}

int main () {
    int Q;
    scanf("%d%s", &Q, s);
    sam::build();
    char op[10];
    while (Q--) {
        scanf("%s", op);
        if (op[0] == 'A') {
            scanf("%s", s);
            get(mask);
            // printf("%s\n", s);
            sam::build ();
        } else {
            scanf("%s", s);
            get(mask);
            // printf("%s\n", s);
            printf("%d\n", sam::query());
        }
    }
    return 0;
}
