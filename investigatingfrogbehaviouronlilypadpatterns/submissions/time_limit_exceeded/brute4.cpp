#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

bool is_free[2'000'007];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	vector<ll> pos(n);
	memset(is_free, 1, sizeof(is_free));
	for (ll i = 0; i < n; i++) {
		cin >> pos[i];
		is_free[pos[i]] = false;
	}
	ll q;
	cin >> q;
	for (ll i = 0; i < q; i++) {
		ll id;
		cin >> id;
		id--;
		is_free[pos[id]] = true;
		pos[id]++;
		while (not (is_free[pos[id]] | is_free[pos[id]+1] | is_free[pos[id]+2] | is_free[pos[id]+3]))
			pos[id] += 4;
		while (not is_free[pos[id]])
			pos[id]++;
		is_free[pos[id]] = false;
		cout << pos[id] << endl;
	}

	return 0;
}
