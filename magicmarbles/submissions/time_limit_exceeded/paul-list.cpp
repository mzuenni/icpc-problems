#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, q;
	cin >> n >> m >> q;

	list<int> a;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		a.push_back(x);
	}
	
	while (q--) {
		int i, x;
		cin >> i >> x;

		auto it = i < ssize(a)-i ? next(begin(a), i) : prev(end(a), size(a)-i);
		it = a.insert(it, x);

		while (it != end(a)) {
			int k = 0, y = *it;
			list<int>::iterator lit = it, rit = it;
			while (lit != begin(a) && *prev(lit) == y) lit--, k++;
			while (rit != end(a) && *rit == y) rit++, k++;
			if (k < m) break;
			it = a.erase(lit, rit);
		}
		cout << size(a) << '\n';
	}
}
