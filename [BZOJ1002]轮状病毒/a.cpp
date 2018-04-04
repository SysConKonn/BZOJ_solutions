#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 110
using namespace std;

int N;

struct bigNum {
    int val[MAX_N], len_;
}f[MAX_N];

bigNum sub (bigNum, bigNum);
bigNum mul (bigNum, int);

int main () {
    scanf("%d", &N);
    f[1].val[1] = 1, f[2].val[1] = 5;
    f[1].len_ = f[2].len_ = 1;
    for (int i = 3;i <= N; ++i) {
	f[i] = sub(mul(f[i - 1], 3), f[i - 2]);
    }
    for (int i = f[N].len_;i > 0; --i) printf("%d", f[N].val[i]);printf("\n");
    return 0;
}

bigNum mul (bigNum a, int k) {
    for (int i = 1;i <= a.len_; ++i) a.val[i] *= k;
    for (int i = 1;i <= a.len_; ++i) a.val[i + 1] += a.val[i] / 10, a.val[i] %= 10;
    while (a.val[a.len_ + 1] != 0) a.len_++;
    // for (int i = a.len;i >= 1; --i) printf("%d", a.val[i]); printf("\n");
    return a;
}

bigNum sub (bigNum a, bigNum b) {
    a.val[1] += 2;
    // for (int i = a.len; i > 0; --i) printf("%d", a.val[i]); printf("\n");
    for (int i = 1;i <= max(a.len_, b.len_); ++i) {
	if (a.val[i] - b.val[i] < 0) a.val[i] += 10, a.val[i + 1] -= 1;
	a.val[i] -= b.val[i];
    }
    while (!a.val[a.len_]) a.len_--;
    return a;
}
