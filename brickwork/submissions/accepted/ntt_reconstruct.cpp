#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll mod = 998244353;
constexpr ll root = 3;
constexpr ll lim = 2ll << 19;	// > 2*w && divides mod - 1 && is pow of 2
constexpr ll its = 18;			// 2^its >= w

ll powMod(ll a, ll b) {
	ll res = 1;
	while (b > 0) {
		if (b & 1) res = (a * res) % mod;
		a = (a * a) % mod;
		b /= 2;
	}
	return res;
}

void fft(vector<ll>& a, bool inverse = 0) {
	int n = sz(a);
	for (int i = 0, j = 1; j < n - 1; ++j) {
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
	for (int s = 1; s < n; s *= 2) {
		ll ws = powMod(root, (mod - 1) / s >> 1);
		if (inverse) ws = powMod(ws, mod - 2);
		for (int j = 0; j < n; j+= 2 * s) {
			ll w = 1;
			for (int k = 0; k < s; k++) {
				ll u = a[j + k], t = a[j + s + k] * w;
				t %= mod;
				a[j + k] = (u + t) % mod;
				a[j + s + k] = (u - t + mod) % mod;
				w *= ws;
				w %= mod;
	}}}
	if (inverse) {
		ll div = powMod(n, mod - 2);
		for (ll i = 0; i < n; i++) {
			a[i] *= div;
			a[i] %= mod;
}}}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, w;
	cin >> n >> w;
	vector<ll> ws(n);
	for (ll& x : ws) cin >> x;
	sort(all(ws));
	ws.erase(unique(all(ws)), ws.end());
	n = sz(ws);

	vector<ll> c(lim);
	c[0] = 1;
	for (ll x : ws) c[x] = 1;

	for (ll i = 0; i < its; i++) {
		fft(c);
		for (ll& x : c) x = (x * x) % mod;
		fft(c, true);
		for (ll j = 0; j <= w; j++) c[j] = min(c[j], 1ll);
		for (ll j = w + 1; j < lim; j++) c[j] = 0;
	}

	c[0] = 2;
	ll res = 0;
	for (ll x : ws) res += c[w - x];

	auto reconstruct = [&](ll first){
		deque<ll> res = {first};
		ll remains = w - first;
		for (ll j = n - 1; j >= 0; j--) {
			while (remains >= ws[j] && c[remains - ws[j]] != 0) {
				remains -= ws[j];
				res.push_back(ws[j]);
			}
		}
		sort(all(res));
		return res;
	};

	if (res <= 1) {
		cout << "impossible" << endl;
	} else {
		cout << "possible" << endl;
		vector<deque<ll>> rows;
		for (ll x : ws) {
			if (c[w - x] != 0) {
				auto row = reconstruct(x);
				ll mi = row[0];
				ll ma = row.back();
				rows.push_back(row);
				if (sz(row) == 1) rows = {row, row};
				if (sz(rows) == 2) break;
				if (mi == ma) continue;
				rows.pop_back();
				
				if (w % ma == 0) {
					row.push_back(mi);
					row.pop_front();
					rows.push_back(row);
					rows.push_back({});
					for (ll i = 0; i < w; i += ma) rows.back().push_back(ma);
					break;
				} else {
					row = reconstruct(ma);
					mi = row[0];
					rows.push_back(row);
					while (row[0] == mi) {
						row.push_back(mi);
						row.pop_front();
					}
					rows.push_back(row);
					break;
				}
			}
		}
		assert(sz(rows) == 2);
		for (auto& v : rows) {
			cout << sz(v) << endl;
			for (ll i = 0; i < sz(v); i++) {
				if (i != 0)	cout << " ";
				cout << v[i];
			}
			cout << endl;
		}
	}
}
