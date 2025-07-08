#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

ll michi(ll n, ll left) {
	if (left > n / 2 + 1 || left < (n + 1) / 2) return 2*n;
	if (n % 2 == 0) return n + n / 2;
	return n;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll l, r;
	cin >> l >> r;
	cout << michi(l+r, l) << endl;
}
