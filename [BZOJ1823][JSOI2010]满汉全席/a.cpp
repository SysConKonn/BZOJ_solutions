#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stack>
#define MAX_N 1007
#define MAX_M 10007

int T, N, M;
int head[MAX_N], to[MAX_N * 2 + MAX_M * 2], nxt[MAX_N * 2 + MAX_M * 2], cap;
int pre[MAX_N], lowlink[MAX_N], scc[MAX_N], scc_cnt, dfn;
int num1[MAX_N], num2[MAX_N];
char ch1[MAX_N], ch2[MAX_N];
std::stack<int>s;

void init();
void add_edge (int, int);
void find_scc ();
void dfs (int);

int main () {
    scanf("%d", &T);
    while (T--) {
    init();
    scanf("%d%d\n", &N, &M);
    for (int i = 1;i <= M; ++i) {
        scanf("%c%d %c%d\n", &ch1[i], &num1[i], &ch2[i], &num2[i]);
        int id1 = ch1[i] == 'm' ? 0 : 1, id2 = ch2[i] == 'm' ? 0 : 1;
        add_edge (num1[i] * 2 + id1 ^ 1, num2[i] * 2 + id2);
        add_edge (num2[i] * 2 + id2 ^ 1, num1[i] * 2 + id1);
    }
    find_scc();
    bool can = true;
    for (int i = 2;i <= N * 2 + 1 && can; i += 2)
        if (scc[i] == scc[i + 1]) can = false;
    if (!can) puts("BAD");
    else puts("GOOD");
    }
    return 0;
}

void init () {
    memset(head, 0, sizeof(head));
    memset(to, 0, sizeof(to));
    memset(nxt, 0, sizeof(nxt));
    memset(pre, 0, sizeof(pre));
    memset(lowlink, 0, sizeof(lowlink));
    memset(scc, 0, sizeof(scc));
    memset(num1, 0, sizeof(num1));
    memset(num2, 0, sizeof(num2));
    memset(ch1, 0, sizeof(ch1));
    memset(ch2, 0, sizeof(ch2));
    cap = scc_cnt = dfn = 0;
}

void dfs (int x) {
    pre[x] = lowlink[x] = ++dfn;
    s.push(x);
    for (int i = head[x]; i; i = nxt[i]) {
    if (!pre[to[i]]) {
        dfs(to[i]);
        lowlink[x] = std::min(lowlink[x], lowlink[to[i]]);
    } else if (!scc[to[i]]) {
        lowlink[x] = std::min(lowlink[x], pre[to[i]]);
    }
    }
    if (lowlink[x] == pre[x]) {
    scc_cnt++;
    while(1) {
        int u = s.top(); s.pop();
        scc[u] = scc_cnt;
        if (u == x) break;
    }
    }
}

void find_scc () {
    memset(pre, 0, sizeof(pre));
    memset(scc, 0, sizeof(scc));
    memset(lowlink, 0, sizeof(lowlink));
    scc_cnt = dfn = 0;
    for (int i = 2;i <= N * 2 + 1; ++i)
    if (!pre[i]) dfs(i);
    //for (int i = 2;i <= N * 2 + 1; ++i) printf("%d ", scc[i]); puts("");
}

void add_edge (int u, int v) {
    //printf("%d %d\n", u, v);
    nxt[++cap] = head[u];
    head[u] = cap;
    to[cap] = v;
}
