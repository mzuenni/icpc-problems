#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

ll calc(ll n, ll left) {
	set<pair<ll, ll>> seen;
	auto add = [&](ll a, ll b) {
		a %= n;
		b %= n;
		if (a > b) swap(a, b);
		seen.insert({a, b});
	};
	for (ll i = 0; i < n; i++) {
		add(i, i + left);
		add(i + left, i + 1);
	}
	return sz(seen);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll l, r;
	cin >> l >> r;
	cout << calc(l+r, l) << endl;
}
