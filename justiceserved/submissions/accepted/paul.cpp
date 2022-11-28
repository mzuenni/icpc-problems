#include <bits/stdc++.h>
using namespace std;

int compress(vector<int> &v) {
	vector<int> i2x = v;
	sort(begin(i2x), end(i2x));
	i2x.erase(unique(begin(i2x), end(i2x)), end(i2x));
	map<int,int> x2i;
	for (int i = 0; i < ssize(i2x); i++) {
		x2i[i2x[i]] = i;
	}
	for (int &x: v) x = x2i[x];
	return size(i2x);
}

struct bit {
	int n;
	vector<int> a;

	bit(int n): n(n), a(n+2) { }
	
	void add(int i, int v) {
		for (i++; i <= n+1; i += i & -i) a[i] = max(a[i], v);
	}
	
	int get(int i) {
		int res = 0;
		for (; i; i -= i & -i) res = max(res,a[i]);
		return res;
	}
};

int main() {
	int n; cin >> n;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> b[i];
		b[i] += a[i];
	}

	compress(a);
	int m = compress(b);

	vector<tuple<int,int,int>> v(n);
	for (int i = 0; i < n; i++) {
		v[i] = {a[i], -b[i], i};
	}
	sort(begin(v), end(v));

	bit B(m);
	vector<int> dp(n);
	for (auto [_,bi,i]: v) {
		bi = -bi;
		dp[i] = 1 + B.get(m-bi);
		B.add(m-1-bi, dp[i]);
	}

	for (int i = 0; i < n; i++) {
		cout << dp[i]-1 << " \n"[i+1==n];
	}
}
