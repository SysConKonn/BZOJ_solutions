#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
#define MAX_N 800010
#define MAX_M 4000010
//#define INF 2147483647
#define INF 100000000
typedef long long ll;
using namespace std;

int N, M, sz, tmp, a[MAX_N];
int ls[MAX_M], rs[MAX_M], key[MAX_M], v[MAX_M], s[MAX_M], w[MAX_M];
int root[MAX_N];

void build (int, int, int, int, int);
void insert (int&, int);
void l_rot (int&);
void r_rot (int&);
void update (int);
void get_rank (int, int, int, int, int, int);
void ask_rank (int, int);
void get_index (int, int, int);
void change (int, int, int, int, int, int);
void del (int&, int);
void get_pre (int, int, int, int, int, int);
void pre (int, int);
void get_nxt (int, int, int, int, int, int);
void nxt (int, int);

int main () {

    scanf("%d%d", &N, &M);
    for (int i = 1;i <= N; ++i) scanf("%d", a + i);
    for (int i = 1;i <= N; ++i) build (1, 1, N, i, a[i]);
    int op, l, r, k;
    for (int i = 1;i <= M; ++i) {
	scanf("%d", &op);
	if (op == 1) {
	    scanf("%d%d%d", &l, &r, &k);
	    tmp = 1;
	    get_rank (1, N, 1, l, r, k);
	    printf("%d\n", tmp);
	}
	else if (op == 2) {
	    scanf("%d%d%d", &l, &r, &k);
	    get_index (l, r, k);
	}
	else if (op == 3) {
	    scanf("%d%d", &l, &k);
	    change (1, N, 1, l, k, a[l]);
	    a[l] = k;
	}
	else if (op == 4) {
	    scanf("%d%d%d", &l, &r, &k);
	    tmp = 0;
	    get_pre (1, N, 1, l, r, k);
	    printf("%d\n", tmp);
	}
	else if (op == 5) {
	    scanf("%d%d%d", &l, &r, &k);
	    tmp = INF;
	    get_nxt (1, N, 1, l, r, k);
	    printf("%d\n", tmp);
	}
    }
    return 0;
}

void nxt (int x, int num) {
    if (!x) return;
    if (v[x] > num) tmp = min(v[x], tmp), nxt (ls[x], num);
    else nxt(rs[x], num);
}

void get_nxt (int l, int r, int x, int totl, int totr, int num) {
    if (l > totr || r < totl) return;
    if (l >= totl && r <= totr) {nxt (root[x], num);return;}
    int mid = l + r >> 1;
    get_nxt (l, mid, x * 2, totl, totr, num);
    get_nxt (mid + 1, r, x * 2 + 1, totl, totr, num);
}

void pre (int x, int num) {
    if (!x) return;
    if (v[x] < num) tmp = max(tmp, v[x]), pre(rs[x], num);
    else pre (ls[x], num);
}

void get_pre (int l, int r, int x, int totl, int totr, int num) {
    if (l > totr || r < totl) return;
    if (l >= totl && r <= totr) {pre (root[x], num);return;}
    int mid = l + r >> 1;
    get_pre (l, mid, x * 2, totl, totr, num);
    get_pre (mid + 1, r, x * 2 + 1, totl, totr, num);
}

void del (int &x, int num) {
    if (v[x] == num) {
	if (w[x] > 1) {s[x]--, w[x]--; return;}
	if (ls[x] * rs[x] == 0) x = ls[x] + rs[x];
	else if (key[ls[x]] < key[rs[x]]) l_rot(x), del(x, num);
	else r_rot (x), del(x, num);
    }
    else if (num < v[x]) del(ls[x], num), s[x]--;
    else del (rs[x], num), s[x]--;
}

void change (int l, int r, int x, int pos, int num, int od) {
    del(root[x], od);insert(root[x], num);
    if (l == r) return;
    int mid = l + r >> 1;
    if (pos <= mid) change (l, mid, x * 2, pos, num, od);
    else change (mid + 1, r, x * 2 + 1, pos, num, od);
}

void get_index (int x, int y, int k) {
    int l = 0, r = INF, mid, ans;
    while (l <= r) {
	mid = l + r >> 1;
	tmp = 1;get_rank (1, N, 1, x, y, mid);
	if (tmp <= k) {l = mid + 1, ans = mid;}
	else r = mid - 1;
    }
    printf("%d\n", ans);
}

void ask_rank (int x, int num) {
    if (!x) return;
    if (v[x] == num) tmp += s[ls[x]];
    else if (num < v[x]) ask_rank (ls[x], num);
    else tmp += s[ls[x]] + w[x], ask_rank (rs[x], num);
}

void get_rank (int l, int r, int x, int totl, int totr, int num) {
    if (l > totr || r < totl) return;
    if (totl <= l && r <= totr) {ask_rank(root[x], num); return;}
    int mid = l + r >> 1;
    get_rank (l, mid, x * 2, totl, totr, num);
    get_rank (mid + 1, r, x * 2 + 1, totl, totr, num);
}

void update (int x) {s[x] = s[ls[x]] + s[rs[x]] + w[x];}

void l_rot (int& x) {
    int y = ls[x];
    ls[x] = rs[y];
    rs[y] = x;
    s[y] = s[x];
    update(x);
    x = y;
}

void r_rot (int& x) {
    int y = rs[x];
    rs[x] = ls[y];
    ls[y] = x;
    s[y] = s[x];
    update(x);
    x = y;
}

void insert (int& x, int num) {
    if (!x) {x = ++sz; s[x] = w[x] = 1; v[x] = num;key[x] = rand();return;}
    s[x]++;
    if (v[x] == num) w[x]++;
    else if (num < v[x]) {insert(ls[x], num); if (key[ls[x]] < key[x]) l_rot (x);} //小根堆
    else {insert(rs[x], num); if (key[rs[x]] < key[x]) r_rot (x);}
}

void build (int x, int l, int r, int k, int num) {
    //printf("%d %d %d %d %d\n", x, l, r, k, num);
    insert (root[x], num);
    if (l == r) return;
    int mid = l + r >> 1;
    if (k <= mid) build (x * 2, l, mid, k, num);
    else build (x * 2 + 1, mid + 1, r, k, num);
}
