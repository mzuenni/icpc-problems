#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, s;
	cin >> n >> s;

	vector<int> a(n);
	for (int &x: a) cin >> x;
	sort(begin(a), end(a));

	auto solve = [&](int m) {
		if (m == 1) return true;
		if (s == 1) return false;
		vector<vector<int>> b(3);
		for (int i = 0; i < m-2; i++) {
			b[a[i]%3].push_back(a[i]);
		}
		long long w = 0;
		for (int x: b[0]) w += x/3;
		int k = min(b[1].size(), b[2].size());
		for (int i = 0; i < k; i++) {
			w += (b[1][i]+b[2][i])/3;
		}
		for (int i = k; i < ssize(b[1]); i += 2) {
			if (i+1 < ssize(b[1])) {
				w += (b[1][i]+1+b[1][i+1])/3;
			} else {
				w += (b[1][i]+2)/3;
			}
		}
		for (int i = k; i < ssize(b[2]); i++) {
			w += (b[2][i]+1)/3;
		}
		return w+2 <= s;
	};

	int lo = 1, hi = n+1;
	while (hi-lo > 1) {
		int md = (lo+hi)/2;
		(solve(md) ? lo : hi) = md;
	}
	cout << lo << '\n';
}
