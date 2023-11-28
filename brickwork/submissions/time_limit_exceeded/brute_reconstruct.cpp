#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ull = unsigned long long;
using ld = long double;

constexpr ll lim = 300'007;
bitset<lim> dp;

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
		if (dp[w]) break;
		bool neq = false;
		for (ll i = x; i <= w; i += x) neq |= dp[i];
		for (ll i = x; i < w; i++) dp[i] = dp[i] | dp[i - x];//hot loop, may be vectorized?
		if (x == w || w % x != 0 || neq) dp[w] = dp[w] | dp[w - x];
	}

	ll divs = 0;
	for (ll x : ws) if (w % x == 0) divs++;

	auto reconstruct = [&](ll first){
		deque<ll> res = {first};
		ll remains = w - first;
		for (ll j = n - 1; j >= 0; j--) {
			while (remains >= ws[j] && dp[remains - ws[j]] != 0) {
				remains -= ws[j];
				res.push_back(ws[j]);
			}
		}
		sort(all(res));
		return res;
	};

	if (dp[w] == 0 && divs < 2) {
		cout << "impossible" << endl;
	} else {
		cout << "possible" << endl;
		vector<deque<ll>> rows;
		for (ll x : ws) {
			if (dp[w - x]) {
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
