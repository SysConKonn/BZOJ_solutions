#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <stack>
#define MAX_N 16020
#define MAX_M 40010
using namespace std;

int N, M;
string s, t;
int mp_cnt, dfn, scc_cnt;
int head[MAX_N], to[MAX_N * 2], nxt[MAX_N * 2], cap;
int pre[MAX_N], lowlink[MAX_N], scc_no[MAX_N];
map<string, int> mp;
int stk[MAX_N], top;

void add_edge (int, int);
void dfs (int);

int main () {
    scanf("%d", &N);
    for (int i = 1;i <= N; ++i) {
	cin >> s;
	mp[s] = ++mp_cnt;
	cin >> s;
	mp[s] = ++mp_cnt;
	add_edge (mp_cnt - 1, mp_cnt);
    }
    scanf("%d", &M);
    for (int i = 1;i <= M; ++i) {
	cin >> s >> t;
	add_edge (mp[t], mp[s]);
    }
    for (int i = 1;i <= N * 2; ++i)
	if (!pre[i]) dfs(i);

    //for (int i = 1;i <= N * 2; ++i) printf("%d ", scc_no[i]); printf("\n");

    for (int i = 1;i <= N; ++i) {
	if (scc_no[i * 2 - 1] == scc_no[i * 2]) puts("Unsafe");
	else puts("Safe");
    }
    return 0;
}

void dfs (int x) {
    pre[x] = lowlink[x] = ++dfn;
    stk[++top] = x;
    for (int i = head[x]; i; i = nxt[i]) {
	if (!pre[to[i]]) {
	    dfs(to[i]);
	    lowlink[x] = min(lowlink[x], lowlink[to[i]]);
	} else if (!scc_no[to[i]]) {
	    lowlink[x] = min(lowlink[x], pre[to[i]]);
	}
    }
    if (lowlink[x] == pre[x]) {
	++scc_cnt;
	while (1) {
	    int y = stk[top--];
	    scc_no[y] = scc_cnt;
	    if (y == x) break;
	}
    }
}

void add_edge (int u, int v) {
    nxt[++cap] = head[u];
    head[u] = cap;
    to[cap] = v;
}
