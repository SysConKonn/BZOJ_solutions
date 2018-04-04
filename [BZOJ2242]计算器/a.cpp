#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
typedef long long ll;
using namespace std;

int T, k;
ll y, z, p;

ll quick_pow (ll, ll, ll);
void bsgs ();

int main () {
    scanf("%d%d", &T, &k);
    while (T--) {
	scanf("%lld%lld%lld", &y, &z, &p);
	y %= p;
	if (k == 1) printf("%lld\n", quick_pow(y, z, p));
	else if (k == 2) {
	    z %= p;
	    if (!y && z) printf("Orz, I cannot find x!\n");
	    else printf("%lld\n", ((z % p) * quick_pow(y, p - 2, p)) % p);
	}
	else bsgs();
    }
    return 0;
}

map<int, int> mp;
void bsgs () {
    z %= p;
    if (!z && !y) {printf("1\n");return;}
    if (!y) {printf("Orz, I cannot find x!\n");return;}
    ll m = ceil(sqrt(p)), t = z;
    mp.clear();
    mp[t] = 0;
    for (int i = 1;i <= m; ++i) {
	t = (t * y) % p;
	mp[t] = i;
    }
    ll base = quick_pow (y, m, p);
    t = 1;
    for (int i = 1;i <= m; ++i) {
	t = (t * base) % p;
	if (mp[t]) {
	    printf("%lld\n", ((i * m - mp[t]) % p + p) % p);
	    return;
	}
    }
    printf("Orz, I cannot find x!\n");
}

ll quick_pow (ll x, ll y, ll mod) { //x ^ y % mod
    ll ans = 1;
    while (y > 0) {
	if (y % 2)
	    ans = (ans * x) % mod;
	x = (x * x) % mod;
	y >>= 1;
    }
    return ans;
}
