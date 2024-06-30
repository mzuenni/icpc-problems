// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll mod = 1e9+7;

ll powMod(ll a, ll b = mod - 2, ll n = mod) {
	ll res = 1;
	while (b > 0) {
		if (b & 1) res = (a * res) % n;
		a = (a * a) % n;
		b /= 2;
	}
	return res;
}

constexpr ll lim = 433;

struct slow {
	vector<ll> data;
	vector<pair<ll, ll>> updates;
	ll mul;
	slow(ll n, ll mul) : data(n), mul(mul){}
	void update(ll pos, ll light) {
		updates.push_back({pos, light});
	}
	void doUpdate() {
		sort(all(updates));
		for (ll i = 0, j = 0, c = 0; i < sz(data); i++) {
			c *= mul;
			while (j < sz(updates) && updates[j].first == i) {
				c += updates[j].second;
				c %= mod;
				j++;
			}
			c %= mod;
			data[i] += c;
		}
		for (ll i = sz(data) - 1, j = sz(updates) - 1, c = 0; i >= 0; i--) {
			c *= mul;
			c %= mod;
			data[i] += c;
			data[i] %= mod;
			while (j >= 0 && updates[j].first == i) {
				c += updates[j].second;
				c %= mod;
				j--;
			}
		}
		updates.clear();
	}
	ll get(ll pos) {
		if (sz(updates) > lim) doUpdate();
		ll res = data[pos];
		for (auto e : updates) {
			res += e.second * powMod(mul, abs(pos - e.first));
			res %= mod;
		}
		return res;
	}
};

constexpr ll decimals = 1000000;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, q;
	ld p;
	cin >> n >> q >> p;
	ll pp = ((decimals - (ll)round(p*decimals)) * powMod(decimals)) % mod;
	slow sol(n, pp);
	for (ll i = 0; i < q; i++) {
		char type;
		cin >> type;
		if (type == '+') {
			ll b, x;
			cin >> b >> x;
			sol.update(x - 1, b);
		} else if (type == '-') {
			ll b, x;
			cin >> b >> x;
			sol.update(x - 1, mod-b);
		} else {
			ll x;
			cin >> x;
			cout << sol.get(x - 1) % mod << "\n";
		}
	}
}
