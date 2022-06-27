#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll inf = 0x3FFFFFFFFFFFFFFF;

ll solve(const vector<ll>& in) {
	ll sum = 0;
	ll ma = 0;
	for (ll x : in) {
		sum += x+1;
		ma = max(ma, x + 1);
	}
	ll res = inf;
	for (ll l = ma; l <= sum; l++) {
		ll rows = 0;
		for (ll i = 0; i < sz(in); rows++) {
			ll c = 0;
			while (i < sz(in) && c + in[i] < l) {
				c += in[i] + 1;
				i++;
			}
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
 
