#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 100007
#define MOD 39989
#define eps 1e-9
#define dcmp(a, b) (((a - b) > eps) - ((a - b) < -eps))
typedef long long ll;

int N, sz;

struct node {
    double k, b;
    ll idx;
    bool vis;
    node () {vis = false, k = b = 0, idx = 0;}
}t[MAX_N * 4];

double K, B;
ll L, R;
ll res_id, lstres;
double res;
ll ans[MAX_N], ans_id[MAX_N];

void query (ll x, ll l, ll r, ll pos) {
    if (l > r || l > pos || r < pos) return;
    double xx = t[x].k * pos + t[x].b;
    if (dcmp(res, xx) < 0 || (dcmp(res, xx) == 0 && t[x].idx < res_id)) res = xx, res_id = t[x].idx;
    if (l == r) return;
    ll mid = l + r >> 1;
    if (pos <= mid) query (x * 2, l, mid, pos);
    else query (x * 2 + 1, mid + 1, r, pos);
}

void solve (ll x, ll l, ll r) {
    if (!t[x].vis) {
        t[x].k = K, t[x].b = B, t[x].idx = sz;
        t[x].vis = true;
        return;
    }
    double y0 = t[x].k * l + t[x].b, y1 = K * l + B;
    double y2 = t[x].k * r + t[x].b, y3 = K * r + B;
    if (dcmp(y1, y0) <= 0 && dcmp(y3, y2) <= 0) return;
    if (dcmp(y1, y0) > 0 && dcmp(y3, y2) > 0) {
        if (dcmp(K, t[x].k) == 0 && dcmp(B, t [x].b) == 0) return;
        t[x].k = K, t[x].b = B, t[x].idx = sz;
        return;
    }
    ll mid = l + r >> 1;
    solve (x * 2, l, mid), solve(x * 2 + 1, mid + 1, r);
}

void insert (ll x, ll l, ll r) {
    if (l > r) return;
    if (L <= l && r <= R) {
        solve(x, l, r);
        return;
    }
    ll mid = l + r >> 1;
    if (L <= mid) insert (x * 2, l, mid);
    if (mid < R) insert (x * 2 + 1, mid + 1, r);
}

int main () {
    scanf("%d", &N);
    int op;
    ll k, x0, y0, x1, y1;
    for (int i = 1;i <= N; ++i) {
        scanf("%d", &op);
        if (op == 0) {
            scanf("%lld", &k);
            k = (k + lstres - 1) % MOD + 1;
            //printf("%d\n", k);
            res = res_id = 0;
            query(1, 1, MOD + 20, k);
            if (res < ans[k] || (res == ans[k] && res_id > ans_id[k]))
                res = ans_id[k];
            lstres = res_id;
            printf("%lld\n", lstres = res_id);
        } else {
            ++sz;
            scanf("%lld%lld%lld%lld", &x0, &y0, &x1, &y1);
            x0 = (x0 + lstres - 1) % MOD + 1;
            y0 = (y0 + lstres - 1) % 1000000000 + 1;
            x1 = (x1 + lstres - 1) % MOD + 1;
            y1 = (y1 + lstres - 1) % 1000000000 + 1;
            if (x0 > x1) std::swap(x0, x1), std::swap(y0, y1);
            //printf("%lld %lld %lld %lld\n", x0, y0, x1, y1);
            if (x0 == x1) {
                if (std::max(y0, y1) > ans[x0]) ans[x0] = std::max(y0, y1), ans_id[x0] = sz;
            } else {
                L = x0, R = x1;
                K = (double)(y1 - y0) / (double)(x1 - x0);
                B = y0 - x0 * K;
                //printf("%lld %lld %lf %lf\n", L, R, K, B);
                insert(1, 1, MOD + 20);
            }
        }
    }
    return 0;
}
