#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 40010
using namespace std;

int N;
int pri[MAX_N], tot, phi[MAX_N];
bool check[MAX_N];
int res;

int main () {
    scanf("%d", &N);
    phi[1] = 1;
    for (int i = 2;i <= N; ++i) {
	if (!check[i]) {
	    pri[++tot] = i;
	    phi[i] = i - 1;
	}
	for (int j = 1;j <= tot; ++j) {
	    if (i * pri[j] > N) break;
	    check[i * pri[j]] = true;
	    if (!(i % pri[j])) {
		phi[i * pri[j]] = pri[j] * phi[i];
		break;
	    }
	    else {
		phi[i * pri[j]] = phi[i] * (pri[j] - 1);
	    }
	}
    }
    for (int i = 1;i < N; ++i) res += phi[i];
    printf("%d\n", res * 2 + 1);
    return 0;
}
