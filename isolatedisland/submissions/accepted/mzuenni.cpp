#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	map<pair<ll, ll>, ll> in;
	for(ll i = 0; i < 2 * n; i++) {
		ll x, y;
		cin >> x >> y;
		in[{x, y}]++;
	}
	for(auto e : in) {
		if(e.second % 2 != 0) {
			cout << "yes" << endl;
			return 0;
		}
	}
	cout << "no" << endl;
}
