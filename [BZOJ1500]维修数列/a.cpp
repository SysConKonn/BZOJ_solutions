/*
 *c分别是结点左右儿子，fa是结点父亲
 *size是子树大小，sum是子树权值和，v是结点权值，mx是当前子树的最大子串和
 *lx是一个子树以最左端为起点向右延伸的最大子串和，rx类似
 *tag是结点的修改标记，修改值为v，rev是翻转标记
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <cstdlib>
#define MAX_N 1000005
#define INF 1000000000
using namespace std;

int N, M, cnt, root;
int a[MAX_N], id[MAX_N], fa[MAX_N], c[MAX_N][2], mx[MAX_N], v[MAX_N], sz[MAX_N];
int lx[MAX_N], rx[MAX_N], sum[MAX_N], tag[MAX_N], rev[MAX_N];
queue<int> q;

void update (int x) {
    int l = c[x][0], r = c[x][1];
    sum[x] = v[x] + sum[l] + sum[r];
    sz[x] = sz[l] + sz[r] + 1;
    mx[x] = max(mx[l], mx[r]);
    mx[x] = max(mx[x], lx[r] + v[x] + rx[l]);
    lx[x] = max(lx[l], sum[l] + v[x] + lx[r]);
    rx[x] = max(rx[r], sum[r] + v[x] + rx[l]);
}

void pushdown (int x) {
    int l = c[x][0], r = c[x][1];
    if (tag[x]) {
        tag[x] = rev[x] = 0;
        if (l) tag[l] = 1, v[l] = v[x], sum[l] = v[x] * sz[l];
        if (r) tag[r] = 1, v[r] = v[x], sum[r] = v[x] * sz[r];
        if (v[x] >= 0) {
            if (l) lx[l] = rx[l] = mx[l] = sum[l];
            if (r) lx[r] = rx[r] = mx[r] = sum[r];
        }
        else {
            if (l) lx[l] = rx[l] = 0, mx[l] = v[x];
            if (r) lx[r] = rx[r] = 0, mx[r] = v[x];
        }
    }
    if (rev[x]) {
        rev[x] ^= 1, rev[l] ^= 1, rev[r] ^= 1;
        swap(lx[l], rx[l]), swap(lx[r], rx[r]);
        swap(c[l][0], c[l][1]), swap(c[r][0], c[r][1]);
    }
}

int find (int x, int k) {
    pushdown(x);
    int l = c[x][0], r = c[x][1];
    if (sz[l] + 1 == k) return x;
    if (sz[l] >= k) return find(l, k);
    return find(r, k - sz[l] - 1);
}

void rotate (int x, int& k) {  
    int y = fa[x], z = fa[y];
    int l = (c[y][1] == x), r = l ^ 1;
    if (y == k) k = x;
    else c[z][c[z][1] == y] = x;
    fa[c[x][r]] = y, fa[y] = x, fa[x] = z;
    c[y][l] = c[x][r], c[x][r] = y;
    update(y), update(x);
}

void splay (int x, int& k) {
    while (x != k) {
        int y = fa[x], z = fa[y];
        if (y != k) 
            if (c[z][0] == y ^ c[y][0] == x) rotate(x, k);
            else rotate(y, k);
        rotate(x, k);
    }
}

void build (int l, int r, int f) {
    if (l > r) return;
    int mid = (l + r) >> 1, now = id[mid], last = id[f];
    if (l == r) {
        sum[now] = a[now], sz[now] = 1;
        tag[now] = rev[now] = 0;
        if (a[l] >= 0) lx[now] = rx[now] = mx[now] = a[l];
        else lx[now] = rx[now] = 0, mx[now] = a[l];
    }
    else build (l, mid - 1, mid), build(mid + 1, r, mid);
    v[now] = a[mid], fa[now] = last, update(now);
    c[last][mid >= f] = now;
}

void insert (int k, int tot) {  //checked!
    for (int i = 1;i <= tot; ++i) scanf("%d", a + i);
    for (int i = 1;i <= tot; ++i) 
        if (!q.empty()) id[i] = q.front(), q.pop();
        else id[i] = ++cnt;
    build(1, tot, 0);
    int z = id[(1 + tot) >> 1];
    int x = find(root, k + 1), y = find(root, k + 2);
    splay(x, root), splay(y, c[x][1]);
    fa[z] = y; c[y][0] = z;
    update(y), update(x);
}

int split (int k, int tot) { //printf("split");
    int x = find(root, k), y = find(root, k + tot + 1); //先将末尾节点翻到根，再将头节点翻到末尾节点下。此时头节点整棵右子树就是待求区间
    splay(x, root), splay(y, c[x][1]);
    return c[y][0];
}

int getsum (int k, int tot) { //printf("getsum");
    int x = split(k, tot);
    return sum[x];
}

void rec (int x) {
    if (!x) return;
    int l = c[x][0], r = c[x][1];
    rec(l); rec(r); q.push(x);
    fa[x] = c[x][0] = c[x][1] = 0;
    tag[x] = rev[x] = 0;
}

void erase (int k, int tot) { //printf("erase\n");
    int x = split(k, tot), y = fa[x];
    rec(x);
    c[y][0] = 0;
    update(y), update(fa[y]);
}

void rever (int k, int tot) { //printf("rever\n");
    int x = split (k, tot), y = fa[x];
    if (!tag[x]) {
        rev[x] ^= 1;
        swap(c[x][0], c[x][1]);
        swap(lx[x], rx[x]);
        update(y), update(fa[y]);
    }
}

void change (int k, int tot, int val) { //printf("change\n");
    int x = split (k, tot), y = fa[x];
    v[x] = val, sum[x] = sz[x] * val, tag[x] = 1;
    if (val >= 0) lx[x] = rx[x] = mx[x] = sum[x];
    else lx[x] = rx[x] = 0, mx[x] = val;
    update(y), update(fa[y]);
}

int main () {
    scanf("%d%d", &N, &M);
    mx[0] = a[1] = a[N + 2] = -INF;
    for (int i = 1;i <= N; ++i) scanf("%d", &a[i + 1]);
    for (int i = 1;i <= N + 2; ++i) id[i] = i;
    build(1, N + 2, 0); 
    root = (N + 3) >> 1, cnt = N + 2;
    char op[10];
    int pos, tot, val;
    for (int i = 1;i <= M; ++i) {
        scanf("%s", op);
        if (op[0] != 'M' || op[2] != 'X') {
            scanf("%d%d", &pos, &tot);
        }
        if (op[0] == 'I') insert(pos, tot);
        if (op[0] == 'G') printf("%d\n", getsum(pos, tot));
        if (op[0] == 'D') erase (pos, tot);
        if (op[0] == 'R') rever (pos, tot);
        if (op[0] == 'M') {
            if (op[2] == 'X') printf("%d\n", mx[root]);
            else scanf("%d", &val), change(pos, tot, val);
        }
    }
    return 0;
}