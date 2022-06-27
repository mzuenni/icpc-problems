#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, q;
	cin >> n >> m >> q;

	vector<int> a(n);
	for (int &x: a) cin >> x;
	reverse(begin(a), end(a));
	
	while (q--) {
		int i, x;
		cin >> i >> x;
		i = size(a)-i;

		a.insert(begin(a)+i, x);
		
		while (i < ssize(a)) {
			int l = i, r = i;
			while (l > 0 && a[l-1] == a[i]) l--;
			while (r < ssize(a) && a[r] == a[i]) r++;
			if (r-l < m) break;
			a.erase(begin(a)+l, begin(a)+r);
			i = l;
		}
		cout << size(a) << '\n';
	}
}
