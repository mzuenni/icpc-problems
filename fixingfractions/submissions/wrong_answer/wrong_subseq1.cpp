#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

ll gcd(ll a, ll b) {return b == 0 ? a : gcd(b, a % b);}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string a, b;
	ll c, d;
	cin >> a >> b >> c >> d; //c and d != 0
	ll bval = stoll(b);

	ll g = gcd(c, d);
	c /= g;
	d /= g;

	for (ll i = 0; i < (1ll << sz(a)); i++) {
		ll ca = 0;
		string na;
		for (ll j = 0, first = true; j < sz(a); j++) {
			if (((i >> j) & 1) == 0 && (!first || a[j] != '0')) {
				ca *= 10;
				ca += a[j] - '0';
				first = false;
			} else {
				na.push_back(a[j]);
			}
		}
		if (ca == 0) continue;
		if ((ca % c) != 0) continue;
		ll cb = (ca / c); //*d
		if (cb > bval/d) continue;
		cb *= d;
		string bs = to_string(cb);
		ll k = 0;
		string nb;
		for (ll j = 0; j < sz(b) && k < sz(bs); j++) {
			if (b[j] == bs[k]) k++;
			else nb.push_back(b[j]);
		}
		sort(all(na));
		sort(all(nb));

		if (k == sz(bs) && na == nb) {
			cout << "possible" << endl;
			cout << ca << " " << cb << endl;
			return 0;
		}
	}
	cout << "impossible" << endl;
}
