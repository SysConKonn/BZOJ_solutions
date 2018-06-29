#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 1000007

int N, M;
int d[MAX_N], v[MAX_N], fa[MAX_N], rs[MAX_N], ls[MAX_N];
bool die[MAX_N];

int merge (int x, int y) {
    if (!x) return y;
    if (!y) return x;
    if (v[x] > v[y]) std::swap(x, y);
    rs[x] = merge(rs[x], y);
    if (d[rs[x]] > d[ls[x]]) std::swap(ls[x], rs[x]);
    d[x] = d[rs[x]] + 1;
    return x;
}

int find (int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}

int main () {
    scanf("%d", &N);
    for (int i = 1;i <= N; ++i) scanf("%d", v + i);
    scanf("%d", &M);
    d[0] = -1;
    for (int i = 1;i <= N; ++i) fa[i] = i;
    char op[10];
    int x, y;
    for (int i = 1;i <= M; ++i) {
	scanf("%s", op);
	if (op[0] == 'M') {
	    scanf("%d%d", &x, &y);
	    if(die[x] || die[y]) continue;
	    int p = find(x), q = find(y);
	    if (p == q) continue;
	    fa[p] = fa[q] = merge(p, q);
	} else {
	    scanf("%d", &x);
	    int p = find(x);
	    if (die[x]) puts("0");
	    else {
		die[p] = true;
		printf("%d\n", v[p]); 
		fa[p] = merge(ls[p], rs[p]);
		fa[fa[p]] = fa[p];  //make it be root
	    }
	}
    }
    return 0;
}
