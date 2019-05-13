#include <cstring>
#include <algorithm>
#include <cstring>
#include <iostream>
#include<stdio.h>
using namespace std;

#define lson rt * 2
#define rson rt * 2 + 1

typedef long long ll;

const int N = 4e5 + 100;

int read() {
	int res = 0; char x = getchar();
	bool is = false;
	while (x != '-' && (x < '0' || x > '9')) x = getchar();
	if (x == '-') is = true, x = getchar();
	while (x >= '0' && x <= '9') res = res * 10 + x - '0', x = getchar();
	if (is) res = -res;
	return res;
}

struct node{
	int st, ed, x, op;
	node() {}
	node(int st, int ed, int x, int op):st(st), ed(ed), x(x), op(op) {}
}mp[N];

bool operator < (node a, node b) {
	return a.x < b.x;
}

int n, tp;
ll tree[N * 4], cnt[N * 4], has[N];

void push_down(int l, int r, int rt) {
	if (cnt[rt] != 0) tree[rt] = has[r + 1] - has[l];
	else if (l == r) tree[rt] = 0;
	else tree[rt] = tree[lson] + tree[rson];
}

void insert(int rl, int rr, int x, int l, int r, int rt) {
	if (rl == l && rr == r) {
		cnt[rt] += x;
		push_down(l, r, rt);
		return;
	}
	int m = (l + r) / 2;
	if (rr <= m) insert(rl, rr, x, l, m, lson);
	else if (m < rl) insert(rl, rr, x, m + 1, r, rson);
	else {
		insert(rl, m, x, l, m, lson);
		insert(m + 1, rr, x, m + 1, r, rson);
	}
	push_down(l, r, rt);
}

void solve() {
	sort(mp, mp + 2 * n);
	ll ans = 0, od = mp[0].x, num = 0;
	for (int i = 0; i < 2 * n; i++) {
		insert(mp[i].st, mp[i].ed, mp[i].op, 0, tp, 1);
		if (mp[i].x == mp[i + 1].x) continue;
		ans += (mp[i].x - od) * num;
		od = mp[i].x;
		num = tree[1];
	}
	printf("%lld\n", ans);
}

int main() {
	//freopen("0in.txt", "r", stdin);
	int a, b, c, d;
	scanf("%d", &n);
	for (int  i = 0; i < n; i++) {
		a = read(), b = read(), c = read(), d = read();
		if (a > c || b > d) swap(a, c), swap(b, d);
		c++, d++;
		mp[i * 2] = node(b, d, a, 1);
		mp[i * 2 + 1] = node(b, d, c, -1);
		has[tp++] = b;
		has[tp++] = d;
	}
	sort(has, has + tp);
	tp = unique(has, has + tp) - has;
	for (int i = 0; i < 2 * n; i++) {
		mp[i].st = lower_bound(has, has + tp, mp[i].st) - has;
		mp[i].ed = lower_bound(has, has + tp, mp[i].ed) - has - 1;
	}
	solve();
	return 0;
}
