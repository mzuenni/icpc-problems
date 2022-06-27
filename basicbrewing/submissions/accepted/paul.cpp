#include <bits/stdc++.h>
using namespace std;

int read_percentage() {
	double x; cin >> x;
	return round(x*1000);
}

int main() {
	int n; cin >> n;
	int p = read_percentage();

	vector<pair<int,int>> a, b;
	while (n--) {
		int c; cin >> c;
		int q = read_percentage();
		if (q <= p) {
			a.emplace_back(p-q, c);
		} else {
			b.emplace_back(q-p, c);
		}
	}
	sort(begin(a), end(a));
	sort(begin(b), end(b));

	int u = 0, v = 0;
	for (auto [q,c]: a) u += q*c;
	for (auto [q,c]: b) v += q*c;

	if (u < v) swap(a,b), swap(u,v);

	double res = 0;
	for (auto [q,c]: b) res += c;
	for (auto [q,c]: a) {
		if (c*q <= v) {
			res += c, v -= c*q;
		} else {
			res += double(v)/q;
			break;
		}
	}
	cout << fixed << setprecision(10) << res << endl;
}
