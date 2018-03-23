#include <cstdio>
#include <iostream>
#include <cstdlib>
#define FOR(i, l, r) for(int i = l;i <= r; ++i) 
#define REP(i, l, r) for(int i = l;i < r; ++i) 
#define out32(d) printf("%d ", d)
#define out64(d) printf("%lld ", d)
#define endl32(d) printf("%d\n", d)
#define endl64(d) printf("%lld\n", d)
#define edl printf("\n")
using namespace std;
#define LIM1 1000
#define LIM2 100000000
#define LIM3 100000

int main () {
	srand(time(0));
	int N = rand()%LIM1, M = rand() % LIM1;
	printf("%d %d\n", N, M);

	int d;
	FOR(i, 1, N) {
		REP(j, 1, M) {
			d = rand() % LIM2;
			out32(d);
		}
		edl;
	}

	REP(i, 1, N) {
		FOR(j, 1, M) {
			d = rand() % LIM2;
			out32(d);
		}
		edl;
	}

	REP(i, 1, N) {
		REP(j, 1, M) {
			d = rand() % LIM2;
			out32(d);
		}
		edl;
	}

	return 0;
}