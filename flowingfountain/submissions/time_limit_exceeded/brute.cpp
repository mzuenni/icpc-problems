#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, q;
	cin >> n >> q;
	vector<ll> lim(n), state(n), next(n, n), cur(n), tmp;
	for (ll& x : lim) cin >> x;
	for (ll i = n - 1; i >= 0; i--) {
		while (!tmp.empty() && lim[tmp.back()] <= lim[i]) tmp.pop_back();
		if (!tmp.empty()) next[i] = tmp.back();
		tmp.push_back(i);
	}
	iota(all(cur), 0);
	for (ll i = 0; i < q; i++) {
		char t;
		ll p;
		cin >> t >> p;
		p--;
		if (t == '+') {
			ll x;
			cin >> x;
			while (x > 0 && cur[p] < n) {
				ll c = min(x, lim[cur[p]] - state[cur[p]]);
				state[cur[p]] += c;
				x -= c;
				if (lim[cur[p]] == state[cur[p]]) cur[p] = next[cur[p]];
			}
		} else {
			cout << state[p] << endl;
		}
	}
}

