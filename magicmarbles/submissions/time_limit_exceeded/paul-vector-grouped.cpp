#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, q;
	cin >> n >> m >> q;

	vector<pair<int,int>> a;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		a.emplace_back(x, 1);
	}
	
	while (q--) {
		int i, x;
		cin >> i >> x;

		int j = 0;
		while (i > 0 && a[j].second <= i) {
			i -= a[j++].second;
		}

		if (i == 0) {
			a.emplace(begin(a)+j, x, 1);
		} else {
			auto [y,k] = a[j];
			if (x == y) {
				a[j].second = k+1;
			} else {
				a[j].second = k-i;
				a.emplace(begin(a)+j, x, 1);
				a.emplace(begin(a)+j, y, i);
				j++;
			}
		}

		n++;

		while (j < ssize(a)) {
			int y = a[j].first, l = j, r = j, k = 0;
			while (l > 0 && a[l-1].first == y) k += a[--l].second;
			while (r < ssize(a) && a[r].first == y) k += a[r++].second;
			a.erase(begin(a)+l, begin(a)+r);
			if (k < m) {
				a.emplace(begin(a)+l, y, k);
				break;
			}
			j = l, n -= k;
		}
		cout << n << '\n';
	}
}
