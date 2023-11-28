#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll width = 3;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, s;
	cin >> n >> s;
	vector<ll> in(n);
	for (ll& x : in) cin >> x;

	sort(all(in));

	ll res = 0;
	for (ll i = 0; i < 2 && s > 0 && n > 0; i++) {
		res++;
		in.pop_back();
		n--;
		s--;
	}
	s *= width;

	ll l = 0;
	ll r = n+1;
	while (l + 1 < r) {
		ll m = (l + r) / 2;
		
		vector<ll> par(width);
		ll sum = 0;
		for (ll i = 0; i < m; i++) {
			sum += in[i];
			par[in[i] % width]++;
		}
		ll free = 0;
		ll todo = abs(par[1] - par[2]);
		if (par[1] < par[2]) {
			free += todo;			
		} else if (par[1] > par[2]) {
			free += todo / 2;
			free += todo % 2;
		}

		if (sum + free <= s) {
			l = m;
		} else {
			r = m;
		}
	}

	cout << l+res << endl;
}
 