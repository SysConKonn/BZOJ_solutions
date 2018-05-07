#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 2200010
#define INF 2147483647
typedef long long ll;

int N, M;
int sum[MAX_N * 4];

inline int read ();
inline void update (int);
inline void insert (int, int, int, int);
inline void del (int, int, int, int);
inline int get_ans (int, int, int, int, int);
inline int get_m (int, int, int, int);
inline bool exist (int, int, int, int);

int main () {
    N = read(); M = read();
    N++;
    int op;
    ll x;
    while (M--) {
	op = read();
	if (op == 3 || op == 4) {
	    if (sum[1] == 0) {puts("-1");continue;}
	    int res = op == 3 ? get_m(1, N, 1, 0) : get_m(1, N, 1, 1);
	    printf("%d\n", res == 0 ? -1 : res - 1);
	}
	else {
	    x = read();
	    if (op == 1) {
		if (!exist(1, N, 1, x + 1))
		    insert (1, N, 1, x + 1);
	    }
	    else if (op == 2) {
		if (exist(1, N, 1, x + 1)) 
		    del (1, N, 1, x + 1);
	    }
	    else if (op == 5) {
		int res = get_ans (1, N, 1, x + 1, 0);
		printf("%d\n", res - 1);
	    }
	    else if (op == 6) {
		int res = get_ans (1, N, 1, x + 1, 1);
		printf("%d\n", res == 0 ? -1 : res - 1);
	    }
	    else if (op == 7) {
		bool res = exist (1, N, 1, x + 1);
		printf("%d\n", res ? 1 : -1);
	    }
	}
    }
    return 0;
}

inline int get_m (int l, int r, int x, int op) {
    if (l > r) return 0;
    if (sum[x] == 0) return 0;
    if (l == r) return l;
    int mid = l + r >> 1;
    if (op == 0) {
	int ans = get_m (l, mid, x * 2, op);
	if (ans) return ans;
	else return get_m (mid + 1, r, x * 2 + 1, op);
    }
    else {
	int ans = get_m (mid + 1, r, x * 2 + 1, op);
	if (ans) return ans;
	else return get_m (l, mid, x * 2, op);
    }
}

inline bool exist (int l, int r, int x, int pos) {
    if (l > r || pos < l || r < pos) return false;
    int mid = l + r >> 1;
    if (sum[x] == 0) return false;
    if (l == r) return sum[x] > 0;
    return exist(l, mid, x * 2, pos) | exist(mid + 1, r, x * 2 + 1, pos);
}

inline int get_ans (int l, int r, int x, int pos, int op) {
    if (l > r) return 0;
    if (op == 0 && l >= pos) return 0;
    if (op == 1 && r <= pos) return 0;
    if (l == r) return sum[x] ? l : 0;
    if (sum[x] == 0) return 0;
    int mid = l + r >> 1;
    if (op == 0) {
	if (mid >= pos) return get_ans (l, mid, x * 2, pos, op);
	int ans = get_ans (mid + 1, r, x * 2 + 1, pos, op);
	if (ans == 0) return get_ans (l, mid, x * 2, pos, op);
	else return ans;
    }
    else {
	if (mid < pos) return get_ans (mid + 1, r, x * 2 + 1, pos, op);
	int ans = get_ans (l, mid, x * 2, pos, op);
	if (ans == 0) return get_ans (mid + 1, r, x * 2 + 1, pos, op);
	else return ans;
    }
}

inline void del (int l, int r, int x, int pos) {
    if (l > r || l > pos || r < pos) return;
    if (l == r) {
	if (sum[x]) sum[x]--;
	return;
    }
    int mid = l + r >> 1;
    del (l, mid, x * 2, pos);
    del (mid + 1, r, x * 2 + 1, pos);
    update(x);
}

inline void update (int x) {sum[x] = sum[x * 2] + sum[x * 2 + 1];}

inline void insert (int l, int r, int x, int pos) {
    if (l > r || l > pos || r < pos) return;
    sum[x]++;
    if (l == r) return;
    int mid = l + r >> 1;
    insert (l, mid, x * 2, pos);
    insert (mid + 1, r, x * 2 + 1, pos);
}

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
