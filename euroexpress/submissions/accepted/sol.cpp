#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;
	ll res = 0;
	for (ll i = 0; i < n; i++) {
		ll a, b;
		cin >> a >> b;
		res = max(res, a * b * min(a, b));
	}
	cout << res << endl;
}
