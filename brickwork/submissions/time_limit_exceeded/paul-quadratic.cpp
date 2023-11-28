#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void print(vector<int> p) {
	cout << size(p) << '\n';
	bool first = true;
	for (int x: p) {
		if (first) first = false;
		else cout << ' ';
		cout << x;
	}
	cout << '\n';
}

void success(vector<int> p, vector<int> q) {
	cout << "possible" << '\n';
	print(p), print(q);
	exit(0);
}

void fail() {
	cout << "impossible" << '\n';
	exit(0);
}

const int W = 333'333;
int dp[W];

int main() {
	int n, w;
	cin >> n >> w;

	vector<int> a(n);
	for (int &x: a) cin >> x;
	sort(begin(a), end(a));
	a.erase(unique(begin(a), end(a)), end(a));
	n = size(a);

	if (find(begin(a), end(a), w) != end(a)) success({w}, {w});

	dp[0] = 1;
	for (int i = 1; i <= w; i++) {
		for (int x: a) {
			if (x > i) break;
			if (dp[i-x]) {
				dp[i] = 1;
				break;
			}
		}
	}

	// Compute up to two partitions of the width into sums of bricks.
	vector<vector<int>> res;
	for (int i = 0; i < n; i++) {
		if (a[i] <= w && dp[w-a[i]]) {
			vector<int> p = {a[i]};
			int r = w-a[i];
			for (int x: a) {
				while (x <= r && dp[r-x]) p.push_back(x), r -= x;
			}
			sort(begin(p), end(p));
			res.push_back(p);
		}
		if (ssize(res) == 2) break;
	}

	if (ssize(res) < 2) fail();

	if (res[0][0] == res[0].back() && res[1][0] == res[1].back()) {
		success(res[0], res[1]);
	}
	
	for (auto p: res) if (p[0] != p.back()) {
		map<int,int> c;
		for (int x: p) c[x]++;

		int x = begin(c)->first, y = next(begin(c))->first;
		i64 z = lcm(i64(x), i64(y));
		while (c[x] > z/x) c[x] -= z/x, c[y] += z/y;

		vector<int> q, r;
		if (c[x] < z/x) {
			q.assign(c[x], x);
			q.resize(c[x]+c[y], y);
			r.assign(c[y], y);
			r.resize(c[x]+c[y], x);
		} else {
			q.assign(c[x]-1, x);
			q.resize(c[x]+c[y]-1, y);
			q.push_back(x);
			r.assign(c[y]+z/y, y);
		}

		vector<int> s;
		for (auto [w,k]: c) if (w > y) while (k--) s.push_back(w);
		q.insert(begin(q)+1, begin(s), end(s));
		r.insert(begin(r)+1, begin(s), end(s));

		success(q, r);
	}
}
