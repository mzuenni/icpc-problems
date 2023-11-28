#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = unsigned long long;
using ld = long double;

ll gcd(ll a, ll b) {return b == 0 ? a : gcd(b, a % b);}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string a, b;
	ll c, d;
	cin >> a >> b >> c >> d; //c and d != 0
	ll aval = stoll(a);

	ll g = gcd(c, d);
	c /= g;
	d /= g;

	for (ll i = 0; i < (1ll << sz(b)); i++) {
		ll cb = 0;
		string nb;
		for (ll j = 0, first = true; j < sz(b); j++) {
			if (((i >> j) & 1) == 0 && (!first || b[j] != '0')) {
				cb *= 10;
				cb += b[j] - '0';
				first = false;
			} else {
				nb.push_back(b[j]);
			}
		}
		if (cb == 0) continue;
		if ((cb % d) != 0) continue;
		ll ca = (cb / d); //*c
		//if (ca > aval/c) continue;
		ca *= c;
		string as = to_string(ca);
		ll k = 0;
		string na;
		for (ll j = 0; j < sz(a); j++) {
			if (k < sz(as) && a[j] == as[k]) k++;
			else na.push_back(a[j]);
		}
		sort(all(na));
		sort(all(nb));

		if (k == sz(as) && na == nb) {
			cout << "possible" << endl;
			cout << ca << " " << cb << endl;
			return 0;
		}
	}
	cout << "impossible" << endl;
}
