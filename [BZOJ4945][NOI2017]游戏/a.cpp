#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stack>
#define MAX_N 200007
#define MAX_M 100007

int N, M, d;
char s[MAX_N];
int a1[MAX_N], b1[MAX_N], chx[MAX_N], cant[MAX_N];
char a2[MAX_N], b2[MAX_N];
int head[MAX_N], to[MAX_N], nxt[MAX_N], cap;
bool flag = false;
int scc[MAX_N], scc_cnt, pre[MAX_N], dfn, lowlink[MAX_N];
std::stack<int> S;

void add_edge (int, int);
void dfs (int);
bool solve ();
void tarjan (int);
int trans (int, char);
int neg (int);

int main () {
    scanf("%d%d", &N, &d); d = 0;
    scanf("%s", s + 1);
    for (int i = 1;i <= N; ++i) if (s[i] == 'x') chx[i] = ++d;
    scanf("%d", &M);
    for (int i = 1;i <= M; ++i) {
        scanf("%d %c %d %c\n", a1 + i, a2 + i, b1 + i, b2 + i);
    }
    dfs(1);
    if (!flag) puts("-1"); 
    return 0;
}

void add_edge (int u, int v) {
    // printf("%d %d\n", u, v);
    nxt[++cap] = head[u];
    head[u] = cap;
    to[cap] = v;
}

int trans (int x, char c) {
    if (s[x] == 'a') return c == 'B' ? x : x + N;
    if (s[x] == 'b' || s[x] == 'c') return c == 'A' ? x : x + N;
    if (c == 'C') return x + N;
    return x;
}

void tarjan (int x) {
    pre[x] = lowlink[x] = ++dfn;
    S.push(x);
    for (int i = head[x]; i; i = nxt[i]) {
        if (!pre[to[i]]) {
            tarjan (to[i]);
            lowlink[x] = std::min(lowlink[x], lowlink[to[i]]);
        } else if (!scc[to[i]]) 
            lowlink[x] = std::min(lowlink[x], pre[to[i]]);
    }
    if (lowlink[x] == pre[x]) {
        ++scc_cnt;
        while (1) {
            int u = S.top();S.pop();
            scc[u] = scc_cnt;
            if (u == x) break;
        }
    }
}

int neg (int x) {return x <= N ? x + N : x - N;}

bool solve () {
    cap = scc_cnt = dfn = 0;
    for (int i = 1;i <= (N << 1); ++i) pre[i] = scc[i] = head[i] = 0;
    for (int i = 1;i <= M; ++i) {
        if (s[a1[i]] != 'x' && s[b1[i]] != 'x') {
            if (a2[i] == s[a1[i]] - 32) continue;
            int u = trans (a1[i], a2[i]), v;
            if (b2[i] == s[b1[i]] - 32) {add_edge (u, neg(u)); continue;}
            v = trans (b1[i], b2[i]);
            add_edge (u, v);
            add_edge (neg(v), neg(u));
        }
        else {
            char p = s[a1[i]], q = s[b1[i]];
            int u, v, x = chx[a1[i]], y = chx[b1[i]];
            int canta = p == 'x' ? cant[x] : p - 32, cantb = q == 'x' ? cant[y] : q - 32;
            //printf("%c %d %c %d  %d %d  %d %d\n", p, x, q, y, canta, cantb, a2[i], b2[i]);
            if (a2[i] == canta) continue;
            u = trans (a1[i], a2[i]);
            if (b2[i] == cantb) {add_edge (u, neg(u)); continue;}
            v = trans (b1[i], b2[i]);
            add_edge (u, v);
            add_edge (neg(v), neg(u));
        }
    }
    for (int i = 1;i <= (N << 1); ++i) if (!pre[i]) tarjan (i);
    for (int i = 1;i <= N; ++i) if (scc[i] == scc[i + N]) return false;
    // printf("%c %c\n", cant[1], cant[2]);
    // for (int i = 1;i <= (N << 1); ++i) printf("%d ", scc[i]); puts("");
    //如果 bel[i]<bel[i']，那么使用该地图适合的第一种赛车，否则使用第二种赛车
    for (int i = 1;i <= N; ++i)  {
        if (scc[i] < scc[i + N]) {
            if (s[i] == 'a') putchar('B');
            else if (s[i] == 'b' || s[i] == 'c') putchar('A');
            else if (cant[chx[i]] == 'A') putchar('B');
            else putchar('A');
        }   else {
            if (s[i] == 'a' || s[i] == 'b') putchar ('C');
            else if (s[i] == 'c') putchar ('B');
            else if (cant[chx[i]] == 'C') putchar ('B');
            else putchar ('C');
        }
    }
    puts("");
    return 1;
}

void dfs (int dep) {
    if (dep > d) {
        if (!flag) flag = solve();
        if (flag) exit(0);
        return;
    }
    cant[dep] = 'A', dfs (dep + 1);
    cant[dep] = 'B', dfs (dep + 1);
} 
