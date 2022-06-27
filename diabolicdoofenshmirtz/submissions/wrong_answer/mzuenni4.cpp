#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	for (ll x = 1;; x *= 3) {
		cout << "? " << x << endl;
		ll res;
		cin >> res;
		if (res != x) {
			cout << "! " << x-res << endl;
			return 0;
		}
	}
}
