#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 2 * 100010
#define MAX_M 100010
using namespace std;

int N, M;
int fa[MAX_N], nxt[MAX_N], q[MAX_N], top, sz[MAX_N], c[MAX_N][2];
bool rev[MAX_N];

void access (int);
bool isroot (int);
void splay (int);
void rotate (int);
void update (int);
void makeroot (int);
void pushdown (int);
void cut (int, int);
void link (int, int);

int main () {
    scanf("%d", &N);
    int x;
    for (int i = 1;i <= N; ++i) {
	scanf("%d", &x);
	fa[i] = nxt[i] = min(N + 1, x + i);
	sz[i] = 1;
    }
    sz[N + 1] = 1;
    scanf("%d", &M);
    for (int i = 1;i <= M; ++i) {
	scanf("%d", &x);
	if (x == 1) { //query_size
	    makeroot(N + 1);
	    scanf("%d", &x);x++;
	    // printf("%d\n", x);
	    access(x), splay(x);
	    printf("%d\n", sz[c[x][0]]);
	}
	else {  //make_change
	    int pos, k;
	    scanf("%d%d", &pos, &k);pos++;
	    // printf("%d %d\n", pos, k);
	    int t = min(N + 1, pos + k);
	    cut(pos, nxt[pos]), link(pos, t), nxt[pos] = t;
	}
    }
    return 0;
}

void link (int x, int y) {
    makeroot(x), fa[x] = y, rev[x] ^= 1;
}

void cut (int x, int y) {
    makeroot(x), access (y), splay(y);
    c[y][0] = fa[x] = 0;
}

inline void makeroot (int x) {
    access (x), splay (x), rev[x] ^= 1;
}

inline void pushdown (int x) {
    int l = c[x][0], r = c[x][1];
    if (rev[x]) {
	rev[x] ^= 1, rev[l] ^= 1, rev[r] ^= 1;
	swap (c[x][0], c[x][1]);
    }
}

inline void update (int x) {
    int l = c[x][0], r = c[x][1];
    sz[x] = sz[l] + sz[r] + 1;
}

inline void rotate (int x) {
    int y = fa[x], z = fa[y];
    int l = c[y][1] == x, r = l ^ 1;
    if (!isroot(y)) c[z][c[z][1] == y] = x;
    fa[x] = z, fa[y] = x, fa[c[x][r]] = y;
    c[y][l] = c[x][r], c[x][r] = y;
    update(y), update(x);
}

inline bool isroot (int x) {return (c[fa[x]][0] != x && c[fa[x]][1] != x);}

inline void splay (int x) { top = 0;
    q[++top] = x;
    for (int i = x; !isroot(i); i = fa[i]) q[++top] = fa[i];
    while (top) pushdown(q[top--]);
    while (!isroot(x)) {
	int y = fa[x], z = fa[y];
	if (!isroot(y))
	    if (c[z][0] == y ^ c[y][0] == x) rotate(x);
	    else rotate(y);
	rotate(x);
    }
}

inline void access (int x) {
    for (int t = 0; x; t = x, x = fa[x])
	splay(x), c[x][1] = t;
}
