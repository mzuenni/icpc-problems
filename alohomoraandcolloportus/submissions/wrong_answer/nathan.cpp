#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ll n, m, a, b;
	cin >> n >> m;
	vector<ll> adj[n];
	ll deg[n] = {0};
	for (ll i = 0; i < m; ++i) {
		cin >> a >> b;
		++deg[--a];
		++deg[--b];
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	ll one = 0, two = 0, other = 0;
	for (ll i = 0; i < n; ++i) {
		if (deg[i] == 1) ++one;
		else if (deg[i] == 2) ++two;
		else ++other;
	}
	for (ll i = 0; i < n; ++i) {
		ll _one = 0, _two = 0, _other = 0;
		if (deg[i] == 1) --_one;
		else if (deg[i] == 2) --_two;
		else --_other;
		for (auto x : adj[i]) {
			if (deg[x] == 1) --_one, ++_other;
			else if (deg[x] == 2) --_two, ++_one;
			else if (deg[x] == 3) --_other, ++_two;
		}
		if (one + _one == 2 && other + _other == 0) {
			cout << "YES" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;
	return 0;
}
