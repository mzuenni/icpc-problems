#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	for (ll x = 2;; x *= 2) {
		cout << "? " << x-1 << endl;
		ll res;
		cin >> res;
		if (res != x-1) {
			cout << "! " << x-1-res << endl;
			return 0;
		}
	}
}
