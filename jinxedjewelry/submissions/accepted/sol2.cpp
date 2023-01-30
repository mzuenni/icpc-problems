#include<bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ld>;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll t;
	cin >> t;
	for (ll i = 0; i < t; i++) {
		ll n;
		cin >> n;
		multiset<ll> in;//sum must be atleast 3 for task
		for (ll j = 0; j < n; j++) {
			ll x;
			cin >> x;
			in.insert(x);
		}
		ll res = 1;
		while (sz(in) >= 3) {
			ll mi = *in.begin();
			in.erase(in.begin());
			ll ma1 = *prev(in.end());
			in.erase(prev(in.end()));
			ll ma2 = *prev(in.end());
			in.erase(prev(in.end()));
			mi--;
			in.insert(ma1 + 1 + ma2);
			if (mi > 0) in.insert(mi);
			res++;
		}
		if (sz(in) == 2 && *in.begin() > 1) {
			res++;
		}
		cout << res << endl;
	}
}
