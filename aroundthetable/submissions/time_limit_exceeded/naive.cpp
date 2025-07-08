#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

ll calc(ll l, ll r) {
	ll n = l + r;
	set<pair<ll, ll>> seen;
	auto add = [&](ll a, ll b) {
		a %= n;
		b %= n;
		if (a > b) swap(a, b);
		seen.insert({a, b});
	};
	deque<ll> left, right;
	for (int i = 0; i < l; i++) left.push_back(i);
	for (int i = 0; i < r; i++) right.push_back(i + l);
	for (int i = 0; i < (l+r); i++) {
		for (int j = 0; j < (l+r); j++) {
			add(left[0], right[0]);
			right.push_back(left[0]);
			left.pop_front();

			add(right[0], left[0]);
			left.push_back(right[0]);
			right.pop_front();
		}
	}
	return sz(seen);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll l, r;
	cin >> l >> r;
	cout << calc(l, r) << endl;
}
