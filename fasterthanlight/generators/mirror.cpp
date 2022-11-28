#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;

struct rect {
	ll x1, y1, x2, y2;
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	vector<rect> in(n);
	ll mi = 0;
	for (ll i = 0; i < n; i++) {
		ll x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		in[i] = {-x2, y1, -x1, y2};
		mi = min(mi, -x2);
	}
	cout << n << endl;
	for (auto& r : in) {
		r.x1 -= mi;
		r.x2 -= mi;
		r.x1++;
		r.x2++;
		cout << r.x1 << " " << r.y1 << " " << r.x2 << " " << r.y2 << endl;
	}
}
