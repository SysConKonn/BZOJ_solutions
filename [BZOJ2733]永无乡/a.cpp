#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 500010
typedef long long ll;

int N, M, sz;
int v[MAX_N], fa[MAX_N], mp[MAX_N], root[MAX_N];
int ls[MAX_N * 4], rs[MAX_N * 4], sum[MAX_N * 4];

int find (int);
void insert (int&, int, int, int);
void update (int);
int query (int, int, int, int);
int merge (int, int);

int main () {
    scanf("%d%d", &N, &M);
    for (int i = 1;i <= N; ++i) scanf("%d", v + i);
    for (int i = 1;i <= N; ++i) fa[i] = i;
    int x, y;
    for (int i = 1;i <= M; ++i) {
	scanf("%d%d", &x, &y);
	x = find(x), y = find(y);
	fa[x] = y;
    }
    for (int i = 1;i <= N; ++i) {
	//printf("%d %d %d\n", i, find(i), v[i]);
	insert(root[find(i)], 1, N, v[i]);
	mp[v[i]] = i;
    }
    char op[3];
    int q;
    scanf("%d", &q);
    for (int i = 1;i <= q; ++i) {
	scanf("%s%d%d", op, &x, &y);
	//printf("%c %d %d\n", op[0], x, y);
	if (op[0] == 'Q') {
	    int t = root[find(x)];
	    if (sum[t] < y) {printf("-1\n"); continue;}
	    printf("%d\n", mp[query(t, 1, N, y)]);
	}
	else {
	    x = find(x), y = find(y);
	    if (x == y) continue;
	    fa[y] = x;
	    root[x] = merge (root[x], root[y]);
	}
    }
    return 0;
}

int merge (int x, int y) {
    if (!x) return y;
    if (!y) return x;
    ls[x] = merge(ls[x], ls[y]);
    rs[x] = merge(rs[x], rs[y]);
    update(x);
    return x;
}

int query (int o, int l, int r, int k) {
    if (!o) return 0;
    if (l == r) return l;
    int mid = l + r >> 1;
    if (k <= sum[ls[o]]) return query (ls[o], l, mid, k);
    else return query (rs[o], mid + 1, r, k - sum[ls[o]]);
}

void update (int x) {sum[x] = sum[ls[x]] + sum[rs[x]];}

void insert (int& o, int l, int r, int val) {
    if (!o) o = ++sz;
    if (l == r) {sum[o]++; return;}
    int mid = l + r >> 1;
    if (val <= mid) insert(ls[o], l, mid, val);
    else insert(rs[o], mid + 1, r, val);
    update(o);
}

int find (int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
