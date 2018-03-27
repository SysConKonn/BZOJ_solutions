/*
写一下各个数组的意义。
e[]存边。
a[]记题中崛起次数
siz[]记子树access次数
f[]记当前点贡献
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 400010
typedef long long ll;
using namespace std;

int N, M;
int head[MAX_N], nxt[MAX_N * 2], to[MAX_N * 2], tmp;
int son[MAX_N], c[MAX_N][2], fa[MAX_N];
ll sz[MAX_N], f[MAX_N], a[MAX_N], tag[MAX_N], res;

inline int input ();
inline void add_edge (int, int);
void dfs (int, int);
void access (int, int);
inline void update (int);
inline void pushup (int);
inline void pushdown (int);
inline void splay (int);
inline void rotate (int);
inline void modify (int, ll);
inline int findleft (int);
inline bool isroot (int);

int main () {
    scanf("%d%d", &N, &M);
    for (int i = 1;i <= N; ++i) a[i] = input();
    int u, v;
    for (int i = 1;i < N; ++i) {
	u = input(), v = input();
	add_edge (u, v);
	add_edge (v, u);
    }
    dfs(1, 0);
    printf("%lld\n", res);
    int x, y;
    for (int i = 1;i <= M; ++i) {
	scanf("%d%d", &x, &y);
	access (x, y);
	printf("%lld\n", res);
    }
    return 0;
}

inline void modify (int x, ll v) {
    if (!x) return;
    sz[x] += v, tag[x] += v;
}

inline bool isroot (int x) {return (c[fa[x]][0] != x) && (c[fa[x]][1] != x);}

inline void pushdown (int x) {
    if (!x) return;
    modify (c[x][0], tag[x]), modify (c[x][1], tag[x]), tag[x] = 0;
}

inline void pushup (int x) {
    if (!isroot(x)) pushup(fa[x]);
    pushdown (x);
}

inline int findleft (int x) {
    while (c[x][0]) pushdown (x), x = c[x][0]; return x;
}

inline void rotate (int x) {
    int y = fa[x], z = fa[y];
    int l = c[y][1] == x, r = l ^ 1;
    if (!isroot(y)) c[z][c[z][1] == y] = x;
    c[y][l] = c[x][r], c[x][r] = y;
    fa[c[y][l]] = y, fa[y] = x, fa[x] = z;
}

inline void splay (int x) {
    pushup (x);
    while (!isroot (x)) {
	int y = fa[x], z = fa[y];
	if (!isroot(y))
	    if ((c[z][1] == y) ^ (c[y][1] == x)) rotate (x);
	    else rotate (y);
	rotate (x);
    }
}

void access (int x, int v) {
    a[x] += v;
    for (int t = 0; x; t = x, x = fa[x]) {
	splay (x); sz[x] += v; modify (c[x][0], v);
	if (son[x]) {
	    pushup (son[x]);
	    if (sz[son[x]] * 2 <= sz[x]) son[x] = c[x][1] = 0;
	}
	int y = findleft (t);
	if (sz[y] * 2 > sz[x]) son[x] = y, c[x][1] = t;
	update(x);
    }
}

inline void update (int x) {
    res -= f[x];
    f[x] = son[x] ? 2 * (sz[x] - sz[son[x]]) : sz[x] - 1;
    if (a[x] * 2 > sz[x]) f[x] = 2 * (sz[x] - a[x]);
    res += f[x];
}

void dfs (int x, int lst) {
    sz[x] = a[x];fa[x] = lst;
    for (int i = head[x]; i; i = nxt[i]) {
	if (to[i] == lst) continue;
	dfs(to[i], x);
	sz[x] += sz[to[i]];
    }
    for (int i = head[x]; i; i = nxt[i]) {
	if (to[i] == lst) continue;
	if (sz[to[i]] * 2 > sz[x]) son[x] = c[x][1] = to[i];
    }
    update(x); //计算初始答案
}

inline void add_edge (int u, int v) {
    nxt[++tmp] = head[u];
    head[u] = tmp;
    to[tmp] = v;
}

inline int input() {
    int x=0,o=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') o=-1,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*o;
}
