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
		vector<ll> in(n);//sum must be atleast 3 for task
		for (ll j = 0; j < n; j++) {
			cin >> in[j];
		}
		sort(all(in));
		ll res = n;
		for (ll j = 0, sum = 0; j < n; j++) {
			ll remain = n-j-1;
			sum += in[j];
			if (sum <= remain) {
				res = min(res, remain);
			} else {
				res = min(res, remain + 1);
				break;
			}
		}
		cout << res << endl;
	}
}
