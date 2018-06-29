#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 107
#define MAX_M 1007
#define MOD 31011

struct edge {
    int u, v, w;
}e[MAX_M];

struct cls {
    int l, r, num;
}a[MAX_M];

int N, M;
int fa[MAX_N];
int cnt, sum, res = 1, sz;

int find (int x) {return x == fa[x] ? x : find(fa[x]);}

void dfs (int id, int x, int k) {
    if (x == a[id].r + 1) {
	if (k == a[id].num) sum++;
	return;
    }
    int p = find(e[x].u), q = find(e[x].v);
    if (p != q) {  //取当前边
	fa[p] = q;
	dfs(id, x + 1, k + 1);
	fa[p] = p, fa[q] = q;
    }
    dfs(id, x + 1, k);
}

bool cmp (const edge a, const edge b) {return a.w < b.w;}

int main () {
    scanf("%d%d", &N, &M);
    for (int i = 1;i <= N; ++i) fa[i] = i;
    for (int i = 1;i <= M; ++i) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    std::sort(e + 1, e + M + 1, cmp);
    for (int i = 1;i <= M; ++i) {
	if (e[i].w != e[i - 1].w) a[++cnt].l = i, a[cnt - 1].r = i - 1;
	int p = find(e[i].u), q = find(e[i].v);
	if (p != q) {
	    a[cnt].num++;
	    fa[p] = q;
	    sz++;
	}
    }
    a[cnt].r = M;
    if (sz != N - 1) return puts("0"), 0; 
    
    for (int i = 1;i <= N; ++i) fa[i] = i;
    for (int i = 1;i <= cnt; ++i) {
	sum = 0;
	dfs(i, a[i].l, 0);
	res = (res * sum) % MOD;
	for (int j = a[i].l;j <= a[i].r; ++j) {
	    int p = find(e[j].u), q = find(e[j].v);
	    if (p != q)
		fa[p] = q;
	}
    }
    printf("%d\n", (res + MOD) % MOD);
    return 0;
}
