#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

ll wendy(ll n, ll left) {
	if (left == 1) return 2*n;
	if ((2*left) % n == 0) return n + n/2;
	if ((2*left) % n == 2) return n + n/2;
	if ((2*left) % n == 1) return n;
	return 2*n;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll l, r;
	cin >> l >> r;
	cout << wendy(l+r, l) << endl;
}
