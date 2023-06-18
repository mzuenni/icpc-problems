#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

// this is O(n*q), specifically _Find_next requires ~ n*q/64 = 1.8*10^8 (very simple)
// operations in total, so we won't be able to rule this solution out

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	vector<ll> pos(n);
	bitset<2000007> free;
	free.set();
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
		pos[id] = free._Find_next(pos[id]);
		free[pos[id]] = false;
		cout << pos[id] << endl;
	}

}
 
