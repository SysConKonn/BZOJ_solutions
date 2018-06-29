#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>

#define MAX_N 400007
#define MAX_M 200007

int N, M, k;
std::vector <int> e[MAX_N];
int a[MAX_N], fa[MAX_N], tot;
bool vis[MAX_N];
int res[MAX_N];

int find (int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}

void add (int x) {
    tot++;
    for (int i = 0;i < e[x].size(); ++i) {
	if (vis[e[x][i]]) continue;
	int p = find(x), q = find(e[x][i]);
	if (p == q) continue;
	tot--, fa[p] = q;
    }
}

int main () {
    scanf("%d%d", &N, &M);
    int u, v;
    for (int i = 1;i <= M; ++i) {
	scanf("%d%d", &u, &v);
	e[u].push_back(v), e[v].push_back(u);
    }
    
    scanf("%d", &k);
    for (int i = 0;i <= N; ++i) fa[i] = i;
    for (int i = 1;i <= k; ++i) scanf("%d", a + i), vis[a[i]] = true;
    for (int i = 0;i < N; ++i) if (!vis[i]) add (i);
    res[k] = tot;
    for (int i = k;i > 0;--i) {
	vis[a[i]] = false;
	add(a[i]);
	res[i - 1] = tot;
    }
    for (int i = 0;i <= k; ++i) printf("%d\n", res[i]); 
    return 0;
}
