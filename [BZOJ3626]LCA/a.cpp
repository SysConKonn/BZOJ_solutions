#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define MAX_N 100010
#define MOD 201314
typedef long long ll;
using namespace std;
struct pro {
    ll id, x;
    bool flag;
};

ll N, q;
int head[MAX_N], to[MAX_N * 2], nxt[MAX_N * 2], fa[MAX_N], tmp;
vector<pro> qur[MAX_N];
ll deep[MAX_N], id[MAX_N], son[MAX_N], top[MAX_N];
ll res[MAX_N];
ll tag[MAX_N * 40], st[MAX_N * 40];

void add_edge (int, int);
void get_deep (int, int);
void get_top (int, int);
ll q_sum (int);
void make_add (int);
void add (int, int, ll, int, int);
void pushdown (ll, int, int);
void update (int);
ll sum (int, int, ll, int, int);

int main () {
    scanf("%lld%lld", &N, &q);
    ll x;
    for (int i = 1;i < N;) {
	scanf("%lld", &x);
	x++, i++;
	add_edge (x, i);
	fa[i] = x;
    }
    ll l, r;
    for (int i = 1;i <= q; ++i) {
	scanf("%lld%lld%lld", &l, &r, &x);
	qur[l].push_back((pro){i, x, 1});
	qur[r + 1].push_back((pro){i, x, 0});
    }

    get_deep (1, 1);
    get_top (1, 1);
    
    #ifdef DEBUG
    for (int i = 1;i <= N; ++i) printf("%d ", deep[i]); printf("\n");
    for (int i = 1;i <= N; ++i) printf("%d ", top[i]); printf("\n");
    for (int i = 1;i <= N; ++i) printf("%d ", fa[i]); printf("\n");
    for (int i = 1;i <= N; ++i) printf("%d ", id[i]); printf("\n");
    #endif

    for (int i = 1;i <= N; ++i) {
	make_add(i);
	if (qur[i].size() == 0) continue;
	for (int j = 0;j < qur[i].size(); ++j) {
	    if (qur[i][j].flag) res[qur[i][j].id] -= q_sum(qur[i][j].x + 1);
	    else res[qur[i][j].id] = (res[qur[i][j].id] + q_sum(qur[i][j].x + 1) + MOD) % MOD;
	}
    }
    for (int i = 1;i <= q; ++i) printf("%lld\n", res[i] % MOD); 
    return 0;
}

ll sum (int l, int r, ll x, int totl, int totr) {
    if (l > r) return 0;
    pushdown(x, l, r);
    if (l > totr || r < totl) return 0;
    if (l >= totl && r <= totr) return st[x];
    int mid = (l + r) >> 1;
    return sum(l, mid, x * 2, totl, totr) + sum (mid + 1, r, x * 2 + 1, totl, totr);
}

ll q_sum (int x) {
    ll ans = 0;
    while (x) {
	ans += sum(1, N, 1, id[top[x]], id[x]);
	ans %= MOD;
	x = fa[top[x]];
    }
    return ans % MOD;
}

void pushdown (ll x, int l, int r) {
    ll ls = x * 2, rs = x * 2 + 1, mid = (l + r) >> 1;
    tag[ls] += tag[x], tag[rs] += tag[x];
    st[ls] += (mid - l + 1) * tag[x], st[rs] += (r - mid) * tag[x];
    tag[x] = 0;
}

void update (int x) {
    ll l = x * 2, r = x * 2 + 1;
    st[x] = st[l] + st[r];
}

void add (int l, int r, ll x, int totl, int totr) {
    if (l > r) return;
    if (l > totr || totl > r) return;
    pushdown (x, l, r);
    if (totl <= l && r <= totr) {
	st[x] += r - l + 1;
	tag[x]++;
	return;
    }
    int mid = (l + r) >> 1;
    add (l, mid, x * 2, totl, totr);
    add (mid + 1, r, x * 2 + 1, totl, totr);
    update (x);
}

void make_add (int x) {
    while (x) {
	add (1, N, 1, id[top[x]], id[x]);
	x = fa[top[x]];
    }
}

ll idx;
void get_top (int x, int tp) {
    top[x] = tp;
    id[x] = ++idx;
    int k = 0;
    for (int i = head[x]; i; i = nxt[i])
	if (son[to[i]] > son[k] && to[i] != fa[x]) k = to[i];
    if (k == 0) return;
    get_top(k, tp);
    for (int i = head[x]; i; i = nxt[i])
	if (to[i] != k && to[i] != fa[x])
	    get_top(to[i], to[i]);
}

void get_deep (int x, int dep) {
    son[x] = 1, deep[x] = dep;
    for (int i = head[x]; i; i = nxt[i]) {
	if (to[i] == fa[x]) continue;
	fa[to[i]] = x;
	get_deep (to[i], dep + 1);
	son[x] += son[to[i]];
    }
}

void add_edge (int u, int v){
    nxt[++tmp] = head[u];
    head[u] = tmp;
    to[tmp] = v;
}
