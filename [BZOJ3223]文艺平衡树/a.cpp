#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 100010
using namespace std;

int N, M;
int id[MAX_N], c[MAX_N][2], fa[MAX_N], sz[MAX_N], root, rev[MAX_N];

void build (int, int, int);
void rever (int, int);
void update (int);
int find (int, int);
void splay (int, int&);
int split (int, int);
void pushdown (int);
void print (int);
void rotate (int, int&);
void print (int);

int main () {
    scanf("%d%d", &N, &M);
    for (int i = 1;i <= N + 2; ++i) id[i] = i;
    build (1, N + 2, 0);root = (N + 3) >> 1;
    int l, r;
    for (int i = 1;i <= M; ++i) {
	scanf("%d%d", &l, &r);
	rever(l, r);
    }
    print (root);
    printf("\n");
    return 0;
}

void print (int x) {
    if (!x) return;
    pushdown(x);
    print(c[x][0]);
    if (id[x] > 1 && id[x] <= N + 1) printf("%d ", x - 1);
    print(c[x][1]);
}

void build (int l, int r, int f) {
    if (l > r) return;
    int mid = (l + r) >> 1, last = id[f], now = id[mid];
    if (l == r) {
	c[last][mid >= f] = now, fa[now] = last;
	sz[now] = 1;
	return;
    }
    build (l, mid - 1, mid), build (mid + 1, r, mid);
    update(now);
    fa[now] = last;
    c[last][mid >= f] = now;
}

int find (int x, int k) {
    pushdown (x);
    int l = c[x][0], r = c[x][1];
    if (sz[l] + 1 == k) return x;
    else if (sz[l] >= k) return find(l, k);
    else return find (r, k - sz[l] - 1);
}

void update (int x) {
    int l = c[x][0], r = c[x][1];
    sz[x] = sz[l] + 1 + sz[r];
}

void p (int x) {
    if (!x) return;
    printf("%d ", x);
    p(c[x][0]);p(c[x][1]);
}

void rever (int l, int r) {
    int x = split (l, r);
    rev[x] ^= 1;
}

int split (int l, int r) {
    int x = find(root, l), y = find(root, r + 2);
    splay(x, root), splay(y, c[root][1]);
    return c[y][0];
}

void pushdown (int x) {
    if (rev[x]) {
	swap(c[x][0], c[x][1]);
	rev[x] ^= 1, rev[c[x][0]] ^= 1, rev[c[x][1]] ^= 1;
    }
}

void rotate (int x, int& k) {
    int y = fa[x], z = fa[y];
    int l = c[y][1] == x, r = l ^ 1;
    if (y == k) k = x;
    else c[z][c[z][1] == y] = x;
    fa[c[x][r]] = y, fa[x] = z, fa[y] = x;
    c[y][l] = c[x][r], c[x][r] = y;
    update(y), update(x);
}

void splay (int x, int& k) {
    while (x != k) {
	int y = fa[x], z = fa[y];
	if (y != k) 
	    if (c[y][0] == x ^ c[z][0] == y) rotate (x, k);
	    else rotate (y, k);
	rotate (x, k);
    }
}
