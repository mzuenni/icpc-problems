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
	vector<ll> pos(n);
	map<ll, ll> frogs;
	for (ll i = 0; i < n; i++) {
		cin >> pos[i];
		if (frogs.empty() || prev(frogs.end())->first + prev(frogs.end())->second != pos[i]) {
			frogs.insert({pos[i], 0});
		}
		prev(frogs.end())->second++;
	}
	ll q;
	cin >> q;
	for (ll i = 0; i < q; i++) {
		ll id;
		cin >> id;
		id--;
		auto it = prev(frogs.upper_bound(pos[id]));
		ll left = pos[id] - it->first;
		ll right = it->second - left;
		if (left == 0) {
			frogs.erase(it);
		} else {
			it->second = left;
		}
		it = frogs.insert({pos[id] + 1, right}).first;
		pos[id] = it->first + it->second - 1;
		if (next(it) != frogs.end() && next(it)->first == it->first + it->second) {
			it->second += next(it)->second;
			frogs.erase(next(it));
		}
		cout << pos[id] << endl;
	}

}
 
