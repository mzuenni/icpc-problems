#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll lim = 2ll << 19;	// > 2*w && divides mod - 1 && is pow of 2
constexpr ll its = 19;			// 2^its >= w
constexpr double PI = acos(-1);

using cplx = complex<double>;

void fft(vector<cplx>& a, bool inverse = 0) {
	int n = sz(a);
	for (int i = 0, j = 1; j < n - 1; ++j) {
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
	for (int s = 1; s < n; s *= 2) {
		double angle = PI / s * (inverse ? -1 : 1);
		cplx ws(cos(angle), sin(angle));
		for (int j = 0; j < n; j+= 2 * s) {
			cplx w = 1;
			for (int k = 0; k < s; k++) {
				cplx u = a[j + k], t = a[j + s + k] * w;
				a[j + k] = u + t;
				a[j + s + k] = u - t;
				if (inverse) a[j + k] /= 2, a[j + s + k] /= 2;
				w *= ws;
}}}}


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

	vector<cplx> c(lim);
	c[0] = 1;
	for (ll x : ws) c[x] = 1;

	for (ll i = 0; i < its; i++) {
		fft(c);
		for (auto& x : c) x *= x;
		fft(c, true);
		for (ll j = 0; j <= w; j++) c[j] = c[j].real() > 0.5 ? 1 : 0;
		for (ll j = w + 1; j < lim; j++) c[j] = 0;
	}

	c[0] = 2;
	ll res = 0;
	for (ll x : ws) res += c[w - x].real();

	auto reconstruct = [&](ll first){
		deque<ll> res = {first};
		ll remains = w - first;
		for (ll j = n - 1; j >= 0; j--) {
			while (remains >= ws[j] && c[remains - ws[j]].real() > 0.5) {
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
			if (c[w - x].real() > 0.5) {
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
			cout << sz(v);
			for (ll x : v) cout << " " << x;
			cout << endl;
		}
	}
}
