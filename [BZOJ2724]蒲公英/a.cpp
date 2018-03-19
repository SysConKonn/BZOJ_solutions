#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#define MAX_N 100010
#define MAX_M 100010
#define sqn 200
using namespace std;

int N, M;
int a[MAX_N], val[MAX_N], blk[MAX_N], id;
int cnt[MAX_N];
int f[sqn * 3][sqn * 3];
map<int, int> mp;
vector<int> v[MAX_N];

void init ();
int query (int, int);
int get (int, int);

int main () {
    scanf("%d%d", &N, &M);
    for (int i = 1;i <= N; ++i) {
	scanf("%d\n", &a[i]);
	if (!mp[a[i]]) {
	    mp[a[i]] = ++id;
	    val[id] = a[i];
	}
	a[i] = mp[a[i]];
	v[a[i]].push_back(i);
    }
    init();
    int l, r, ans = 0;
    for (int i = 1;i <= M; ++i) {
	scanf("%d%d", &l, &r);
	l = (l + ans - 1) % N + 1, r = (r + ans - 1) % N + 1;
	if (l > r) swap(l, r);
	ans = val[query(l, r)];
	printf("%d\n", ans);
    }
    return 0;
}

int get (int l, int r, int x) {
    return upper_bound (v[x].begin(), v[x].end(), r) - lower_bound(v[x].begin(), v[x].end(), l);
}

int query (int l, int r) {
    int ans, mx;
    ans = f[blk[l] + 1][blk[r] - 1];
    mx = get (l, r, ans);
    for (int i = l;i <= min(blk[l] * sqn, r); ++i) {
	int t = get (l, r, a[i]);
	if (t > mx || (t == mx && val[a[i]] < val[ans])) ans = a[i], mx = t;
    }
    if (blk[l] == blk[r]) return ans;
    for (int i = (blk[r] - 1) * sqn + 1;i <= r; ++i) {
	int t = get (l, r, a[i]);
	if (t > mx || (t == mx && val[a[i]] < val[ans])) ans = a[i], mx = t;
    }
    return ans;
}

void init () {
    for (int i = 1;i <= N; ++i) blk[i] = (i - 1) / sqn + 1;
    // for (int i = 1;i <= blk[N]; ++i) {
    // 	for (int j = blk[i - 1] * sqn + 1;j <= min(blk[i] * sqn, N); ++j) printf("%d ", a[j]);printf("\n");

    // }
    for (int i = 1;i <= blk[N]; ++i) {
	memset(cnt, 0, sizeof(cnt));
	int mx = 0, ans = 0;
	for (int j = (i - 1) * sqn + 1;j <= N; ++j) {
	    cnt[a[j]]++;
	    int t = blk[j];
	    if (cnt[a[j]] > mx || (cnt[a[j]] == mx && val[a[j]] < val[ans]))
		ans = a[j], mx = cnt[a[j]];
	    f[i][t] = ans;
	    //printf("%d %d -> %d\n", i, t, f[i][t]);
	}
    }
}
