#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;


constexpr ll LIM_N = 100007;
constexpr ll LIM_K = 4;
constexpr ll INF = 0x3FFFFFFFFFFF;
ll dp[LIM_K][1 << LIM_K][LIM_N];

void assign_min(ll& l, ll r) {
	if (r < l) l = r;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	auto id = [&](char c) {
		if (c == 'c') return 0;
		if (c == 'd') return 1;
		if (c == 'h') return 2;
		if (c == 's') return 3;
		return -1;
	};

	string s;
	cin >> s;
	ll n = sz(s);

	for (ll i = 1; i <= n; i++) {
		for (ll last = 0; last < LIM_K; last++) {
			for (ll mask = 0; mask < (1 << LIM_K); mask++) {
				dp[last][mask][i] = INF;
			}
		}
	}

	for (ll i = 1; i <= n; i++) {
		ll cur = id(s[i - 1]);
		for (ll last = 0; last < LIM_K; last++) {
			for (ll mask = 0; mask < (1 << LIM_K); mask++) {
				if ((mask | (1 << last)) != mask) continue;
				if (cur == last) {
					assign_min(dp[last][mask][i], dp[last][mask][i-1]);
				} else if ((mask | (1 << cur)) == mask) {
					assign_min(dp[last][mask][i], dp[last][mask][i - 1] + 1);
				} else {
					assign_min(dp[last][mask][i], dp[last][mask][i - 1] + 1);
					assign_min(dp[cur][mask | (1ll << cur)][i], dp[last][mask][i - 1]);
				}
			}
		}
	}
	ll res = n;
	for (ll last = 0; last < LIM_K; last++) {
		for (ll mask = 0; mask < (1 << LIM_K); mask++) {
			if ((mask | (1 << last)) != mask) continue;
			assign_min(res, dp[last][mask][n]);
		}
	}
	cout << res << endl;
}
