#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAX_N 600007

char s[MAX_N];
int mask, len, Q;

namespace sam {
    int root = 1, last = 1, sz = 1;

    struct node {
	int fa, mx, rt;
	int go[30];
	node () {}
	node (int _mx) : fa(0), mx(_mx), rt(0) {
	    memset(go, 0, sizeof(go));
	}
    }t[MAX_N * 5];

    void insert (int c) {
	int p = last, np = ++sz;
	t[np] = node(t[last].mx + 1);
	while (p && !t[p].go[c])
	    t[p].go[c] = np, p = t[p].fa;
	if (!p)
	    t[np].fa = root;
	else {
	    int q = t[p].go[c];
	    if (t[q].mx == t[p].mx + 1) {
		t[np].fa = q;
	    } else {
		int nq = ++sz;
		t[nq] = node(t[p].mx + 1);
		memcpy (t[nq].go, t[q].go, sizeof(t[q].go));
		t[nq].fa = t[q].fa;
		t[q].fa = t[np].fa = nq;
		t[nq].rt = t[q].rt;
		while (p && t[p].go[c] == q)
		    t[p].go[c] = nq, p = t[p].fa;
	    }
	}
	last = np;
	while (np)
	    t[np].rt++, np = t[np].fa;
    }
};

void decode (char *ss, int _mask) {
    int len = strlen(ss);
    for (int i = 0;i < len; ++i) {
	_mask = (_mask * 131 + i) % len;
	std::swap(ss[i], ss[_mask]);
    }
}

void solve () {
    char op[10];
    for (int i = 1;i <= Q; ++i) {
	scanf("%s%s", op, s);
	decode (s, mask);
	len = strlen(s);
	if (op[0] == 'A') {
	    for (int j = 0;j < len; ++j)
		sam::insert(s[j] - 'A' + 1);
	} else {
	    int p = sam::root;
	    for (int j = 0;j < len; ++j) {
		if (!sam::t[p].go[s[j] - 'A' + 1]) {puts("0"); break;}
		p = sam::t[p].go[s[j] - 'A' + 1];
		if (j == len - 1) mask ^= sam::t[p].rt, printf("%d\n", sam::t[p].rt);
	    }
	}
    }
}

int main () {
    scanf("%d%s", &Q, s);
    len = strlen(s);
    for (int i = 0;i < len; ++i) sam::insert(s[i] - 'A' + 1);
    solve ();
    return 0;
}
