#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

ll solve(const vector<ll>& in) {
	vector<ll> pref = {0};
	ll ma = 1;
	for (ll x : in) {
		pref.push_back(pref.back() + x + 1);
		ma = max(ma, x + 1);
	}
	vector<ll> inv(2*pref.back() + 5, 0);
	for (ll i = 0; i < sz(pref); i++) inv[pref[i]] = i;
	for (ll i = 1; i < sz(inv); i++) {
		inv[i] = max(inv[i], inv[i - 1]);
	}
	ll res = pref.back() + 1;
	for (ll l = ma; l <= pref.back() && l + (pref.back() + l - 1) / l < res; l++) {
		ll rows = 0;
		for (ll i = 0; i < sz(in); rows++) {
			ll lim = pref[i] + l;
			i = inv[lim];
		}
		res = min(res, l - 1 + rows);
	}
	return res;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	while (cin >> n) {
		vector<ll> in(n);
		for (ll i = 0; i < n; i++) {
			string s;
			cin >> s;
			in[i] = sz(s);
		}
		cout << solve(in) << endl;
	}
}
 
