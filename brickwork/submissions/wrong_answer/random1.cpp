#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ull = unsigned long long;
using ld = long double;

constexpr ll lim = 300'007;
bitset<lim> dp;

bool ok(const vector<ll>& a, const vector<ll>& b) {
	for (ll i = 1, j = 1, wi = a[0], wj = b[0]; i < sz(a) && j < sz(b);) {
		if (wi == wj) return false;
		if (wi < wj) {
			wi += a[i];
			i++;
		} else {
			wj += b[j];
			j++;			
		}
	}
	return true;
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
	for (ll x : ws) dp[x] = true;
	for (ll i = 0; i < w; i++) {
		if (!dp[i]) continue;
		dp |= dp << i;
	}

	if (dp[w]) {
		mt19937 rng(123456789);
		vector<vector<ll>> tries;
		for (ll i = 0; i < 1000; i++) {
			shuffle(all(ws), rng);
			tries.push_back({});
			for (ll j = 0, c = w; j < n; j++) {
				while (ws[j] <= c && dp[c - ws[j]]) {
					c -= ws[j];
					tries.back().push_back(ws[j]);
				}
			}
			//shuffle(all(tries.back()), rng);
		}

		for (ll i = 0; i < sz(tries); i++) {
			for (ll j = 0; j < i; j++) {
				if (ok(tries[i], tries[j])) {
					cout << "possible" << endl;
					cout << sz(tries[i]) << endl;
					for (ll x : tries[i]) cout << x << " ";
					cout << endl;
					cout << sz(tries[j]) << endl;
					for (ll x : tries[j]) cout << x << " ";
					cout << endl;
					return 0;
				}
			}
		}
	}
	cout << "impossible" << endl;
}
