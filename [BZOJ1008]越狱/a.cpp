#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MOD 100003
typedef long long ll;
using namespace std;

ll N, M;

ll quick_pow (ll, ll);

int main () {
    scanf("%lld%lld", &M, &N);
    printf("%lld\n", (quick_pow(M, N) % MOD - quick_pow (M - 1, N - 1) * M % MOD + MOD) % MOD);
    return 0;
}

ll quick_pow (ll x, ll y) {  //x ^ y % MOD
    ll ans = 1;
    while (y > 0) {
	if (y % 2) ans = (ans * x) % MOD;
	x = (x * x) % MOD;
	y >>= 1;
    }
    return ans;
} 
