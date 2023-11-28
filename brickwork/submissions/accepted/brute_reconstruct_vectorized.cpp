#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ull = unsigned long long;
using ld = long double;

constexpr ll lim = 300'007;
ull dp[lim / 64 + 7]; 

bool getDp(ll i) {
	return (dp[i / 64] >> (i & 63)) & 1;
}

void clearDp(ll i) {
	dp[i / 64] &= ~(1ll << (i & 63));
}

void orDp(ll i, ll value) {
	dp[i / 64] |= value << (i & 63);
}

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

	dp[0] = 1;
	for (ll x : ws) {
		if (getDp(w)) break;
		bool neq = false;
		for (ll i = x; i <= w; i += x) neq |= getDp(i);
		if (x < 64) {//multiple set operations for same ull
			for (ll i = x; i < w; i++) orDp(i, getDp(i - x));
		} else {
			ll ia = x / 64;
			ll ib = x & 63;
			for (ll i = 0; 64*i+x < w; i++) {
				dp[i + ia] |= dp[i] << ib;
				if (ib != 0) dp[i + ia + 1] |= dp[i] >> (64 - ib);
			}
			clearDp(w);//we know it wasnt set before
		}
		if (x == w || w % x != 0 || neq) orDp(w, getDp(w - x));
	}

	ll divs = 0;
	for (ll x : ws) if (w % x == 0) divs++;

	auto reconstruct = [&](ll first){
		deque<ll> res = {first};
		ll remains = w - first;
		for (ll j = n - 1; j >= 0; j--) {
			while (remains >= ws[j] && getDp(remains - ws[j])) {
				remains -= ws[j];
				res.push_back(ws[j]);
			}
		}
		sort(all(res));
		return res;
	};

	if (!getDp(w) && divs < 2) {
		cout << "impossible" << endl;
	} else {
		cout << "possible" << endl;
		vector<deque<ll>> rows;
		for (ll x : ws) {
			if (getDp(w - x)) {
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
