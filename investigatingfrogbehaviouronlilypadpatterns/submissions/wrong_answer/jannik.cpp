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
	set<ll> free;
	for (ll i = 0; i < 2000007; i++) free.insert(i);
	for (ll i = 0; i < n; i++) {
		cin >> pos[i];
		free.erase(pos[i]);
	}
	ll q;
	cin >> q;
	for (ll i = 0; i < q; i++) {
		ll id;
		cin >> id;
		id--;
		auto it = free.insert(pos[id]).first;
		it++;
		pos[id] = *it;
		cout << pos[id] << endl;
	}

}
 
