#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 80000 + 10
#define MOD 1000000
using namespace std;

int N, t, root, sz;
int c[MAX_N][2], v[MAX_N], fa[MAX_N];
int l, r;
long long res;

void ins (int&, int, int);
void splay (int, int&);
void rotate (int);
void get_pre (int, int);
void get_nxt (int, int);
void del (int);

int main () {
    scanf("%d", &N);
    int b, val;
    for (int i = 1;i <= N; ++i) {
        l = r = 0;
        scanf("%d%d", &b, &val);
        //printf("%d\n", root);
        if (!root) {t = b;ins(root, 0, val);}
        else if (b == t) ins(root, 0, val);
        else {
            get_pre (root, val); get_nxt(root, val);
            //printf("%d %d %d\n", i, v[l], v[r]);
            if (!l) {res = (res + v[r] - val) % MOD;del(r);}
            else if (!r) {res = (res + val - v[l]) % MOD, del (l);}
            else {
                if (v[r] - val == val - v[l]) res = (res + val - v[l]) % MOD, del(l);
                else if (v[r] - val > val - v[l]) res = (res + val - v[l]) % MOD, del(l);
                else res = (res + v[r] - val) % MOD, del (r);
            }
        }
    }
    printf("%d\n", res);
    return 0;
}

void del (int x) {
    //printf("%d  %d %d\n", x, c[x][0], c[x][1]);
    splay(x, root);
    if (!(c[x][0] * c[x][1])) {root = c[x][0] + c[x][1];}
    else {
        int k = c[x][1];
        while (c[k][0]) k = c[k][0];
        fa[c[x][0]] = k, c[k][0] = c[x][0];root = c[x][1];
    }
    fa[root] = 0;
}

void rotate (int x, int& k) {
    int y = fa[x], z = fa[y];
    int l = (c[y][1] == x), r = l ^ 1;
    if (y == k) k = x;
    else c[z][c[z][1] == y] = x;
    fa[c[x][r]] = y, fa[y] = x, fa[x] = z;
    c[y][l] = c[x][r], c[x][r] = y;
}

void splay (int x, int& k) {
    while (x != k) {
        int y = fa[x], z = fa[y];
        if (y != k)
            if ((c[y][0] == x) ^ (c[z][0] == y)) rotate (x, k);
            else rotate (y, k);
        rotate (x, k);
    }
}

void ins (int& x, int f, int val) {
    if (!x) {x = ++sz, v[x] = val, fa[x] = f, splay(x, root);return;}
    int d = val >= v[x];
    ins(c[x][d], x, val);
}

void get_nxt (int x, int val) {
    if (!x) return;
    if (v[x] >= val) r = x, get_nxt(c[x][0], val);
    else get_nxt (c[x][1], val);
}

void get_pre (int x, int val) {
    if (!x) return;
    if (v[x] <= val) l = x, get_pre (c[x][1], val);
    else get_pre(c[x][0], val);
}