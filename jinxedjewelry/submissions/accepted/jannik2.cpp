#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
	ll t; cin >> t;
	while (t-->0) {
		ll n; cin >> n;
		deque<ll> a;
		for (ll i = 0; i < n; i++) {
			ll x; cin >> x;
			a.emplace_back(x);
		}
		sort(a.begin(), a.end());
		ll res = 0;
		for (; a.size() >= 3; res++) {
			a.pop_back();
			if (--a.front() == 0) a.pop_front();
		}
		if (a.size() == 2)
			if (a.front() > 1) res++; // merge the two chains
		res++; // join single remaining chain
		cout << res << endl;
	}
	return 0;
}
