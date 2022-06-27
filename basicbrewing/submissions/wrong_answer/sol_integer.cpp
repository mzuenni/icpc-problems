#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll mul = 1000;//required precision

ll readPercentage() {
	ld x;
	cin >> x;
	return round(x*mul);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	ll p = readPercentage();
	ll sum = 0;
	vector<pair<ll, ll>> less, more;
	for (ll i = 0; i < n; i++) {
		ll c;
		cin >> c;
		c *= mul;
		ll cp = readPercentage();
		if (cp <= p) sum += c, less.push_back({cp, c});
		else more.push_back({cp, c});
	}

	sort(all(less));
	reverse(all(less));
	sort(all(more));

	auto calc = [&](ll x){
		ll total = 0;
		ll part = 0;
		for (auto e : less) {
			ll y = min(e.second, x-total);
			total += y;
			part += y*e.first;
		}
		for (auto e : more) {
			ll y = e.second;
			total += y;
			part += y*e.first;
		}
		return part >= p*total;
	};

	ll l = 0;
	ll r = sum+1;
	while (l + 1 < r) {
		ll m = (l + r) / 2;
		if (calc(m)) {
			l = m;
		} else {
			r = m;
		}
	}
	ll total = 0;
	ll part = 0;
	for (auto e : less) {
		ll y = min(e.second, l-total);
		total += y;
		part += y*e.first;
	}
	for (auto e : more) {
		ll y = min(e.second, (p*total-part)/(e.first-p));
		total += y;
		part += y*e.first;
	}
	cout << fixed << setprecision(10) << (ld)total/mul << endl;
}
