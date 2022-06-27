#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, q;
	cin >> n >> m >> q;

	list<pair<int,int>> a;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		a.emplace_back(x, 1);
	}
	
	while (q--) {
		int i, x;
		cin >> i >> x;

		auto it = begin(a);
		while (i > 0 && it->second <= i) {
			i -= (it++)->second;
		}

		if (i == 0) {
			it = a.emplace(it, x, 1);
		} else {
			auto [y,k] = *it;
			if (x == y) {
				it->second = k+1;
			} else {
				it->second = k-i;
				it = a.emplace(it, x, 1);
				it = next(a.emplace(it, y, i));
			}
		}

		n++;

		while (it != end(a)) {
			int k = 0, y = it->first;
			list<pair<int,int>>::iterator lit = it, rit = it;
			while (lit != begin(a) && prev(lit)->first == y) k += (--lit)->second;
			while (rit != end(a) && rit->first == y) k += (rit++)->second;
			it = a.erase(lit, rit);
			if (k < m) {
				a.emplace(it, y, k);
				break;
			}
			n -= k;
		}
		cout << n << '\n';
	}
}
