#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 200010
#define INF 2147483647
typedef long long ll;
using namespace std;

int N, M, top;
int u[MAX_N], v[MAX_N];
ll w[MAX_N], mx[MAX_N], sum[MAX_N];
int fa[MAX_N], c[MAX_N][2], res[MAX_N], q[MAX_N], rev[MAX_N];

bool isroot (int x) {return (c[fa[x]][0] != x && c[fa[x]][1] != x);}

void pushdown (int x) {
    int l = c[x][0], r = c[x][1];
    if (rev[x]) {
        rev[x] ^= 1, res[l] ^= 1, res[r] ^= 1;
        swap(c[x][0], c[x][1]);
    }
}

void update (int x) {
    int l = c[x][0], r = c[x][1];
    sum[x] = sum[l] + sum[r] + w[x];
    mx[x] = max(w[x], max(mx[l], mx[r]));
}

void rotate (int x) {
    int y = fa[x], z = fa[y];
    int l = (c[y][1] == x), r = l ^ 1;
    if (!isroot(y)) c[z][c[z][1] == y] = x;
    fa[c[x][r]] = y, fa[x] = z, fa[y] = x;
    c[y][l] = c[x][r], c[x][r] = y;
    update(y); update(x);
}

void splay (int x) {
    q[++top] = x;
    for (int i = x; !isroot(i); i = fa[i]) q[++top] = fa[i];
    while(top) pushdown(q[top--]);
    while (!isroot(x)) {
        int y = fa[x], z = fa[y];
        if (!isroot(y)) 
            if (c[y][0] == x ^ c[z][0] == y) rotate(x);
            else rotate(y);
        rotate(x);
    }
}

void access (int x) {
    for (int t = 0; x; t = x, x = fa[x]) 
        splay(x), c[x][1] = t, update(x);
}

void make_root (int x) {
    access(x); /*printf("111111\n");*/ splay(x);rev[x] ^= 1;
}

void link (int x, int y) {
    make_root(x); fa[x] = y;
    //printf("111111\n");
}

void split(int x, int y) {
    make_root(x), access(y), splay(y);
}

int main () {
    scanf("%d", &N);mx[0]= -INF;
    for (int i = 1;i < N; ++i) scanf("%d%d", &u[i], &v[i]);
    for (int i = 1;i <= N; ++i) {
        scanf("%lld", w + i);
        sum[i] = mx[i] = w[i];
    }
    //for (int i = 1;i < N; ++i) printf("%d %d\n", u[i], v[i]);
    for (int i = 1;i < N; ++i) link(u[i], v[i]);//, printf("111111\n");
    scanf("%d", &M);
    char op[10];
    int x, y;
    for (int i = 1;i <= M; ++i) {
        scanf("%s%d%d", op, &x, &y);
        if (op[1] == 'H') {
            splay(x);
            w[x] = y;
            update(x);
        }
        else if (op[1] == 'M') 
            split(x, y), printf("%lld\n", mx[y]);
        else split(x, y), printf("%lld\n", sum[y]);
    }
}