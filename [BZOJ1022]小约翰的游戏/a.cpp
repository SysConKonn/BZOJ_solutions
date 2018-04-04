#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

int t, Xor, k, N;

int main () {
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &N);
	int x;
	k = Xor = 0;
	for (int i = 1;i <= N; ++i) {
	    scanf("%d", &x);
	    k += x > 1;
	    Xor ^= x;
	}
	if ((!k && !Xor) || (k && Xor)) puts("John");
	else puts("Brother");
    }
    return 0;
}
