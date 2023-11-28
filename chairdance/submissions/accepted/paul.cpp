#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

tuple<i64,i64,i64> eea(i64 a, i64 b) {
	if (b == 0) return {a, 1, 0};
	auto [g,s,t] = eea(b,a%b);
	return {g, t, s-t*(a/b)};
}

i64 inv_mod(i64 a, i64 m) {
	return get<1>(eea(a, m));
}

int main() {
	int n, q;
	cin >> n >> q;

	i64 a = 1, b = 0;

	vector<int> p(n);
	iota(begin(p), end(p), 0);

	while (q--) {
		char c; cin >> c;
		int x; cin >> x;
		if (c == '+') {
			b = (b+x) % n;
		} else if (c == '*') {
			i64 na = a*x % n, nb = b*x % n;
			if (gcd(na, n) != gcd(a, n)) {
				vector<vector<pair<int,int>>> clash(n);
				for (int i = 0; i < n; i++) {
					int from = (a*i+b) % n, to = (na*i+nb) % n;
					int dist = from <= to ? to-from : to-from+n;
					if (p[i] != i) dist = n+1;
					clash[to].emplace_back(dist, i);
				}
				for (auto v: clash) if (!v.empty()) {
					int i = min_element(begin(v), end(v))->second;
					for (auto [_,j]: v) p[j] = i;
				}
			}
			a = na, b = nb;
		} else if (c == '?') {
			int g = gcd(a, n);
			if ((x-b) % g == 0) {
				int i = ((x-b)/g) * inv_mod(a/g, n/g) % n;
				i = p[(i+n) % n];
				cout << (i ? i : n) << '\n';
			} else {
				cout << -1 << '\n';
			}
		} else {
			assert(0);
		}
	}
}
