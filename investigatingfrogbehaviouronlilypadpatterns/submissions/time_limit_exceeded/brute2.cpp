#include <iostream>
#include <vector>
#include <algorithm>

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
	vector<ll> pos(n);
	vector<bool> free(2'000'007, true);
	for (ll i = 0; i < n; i++) {
		cin >> pos[i];
		free[pos[i]] = false;
	}
	ll q;
	cin >> q;
	for (ll i = 0; i < q; i++) {
		ll id;
		cin >> id;
		id--;
		free[pos[id]] = true;
		pos[id] = distance(free.begin(), find(free.begin() + pos[id] + 1, free.end(), true));
		free[pos[id]] = false;
		cout << pos[id] << endl;
	}

	return 0;
}
