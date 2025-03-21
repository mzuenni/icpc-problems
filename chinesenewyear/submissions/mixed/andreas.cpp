// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <map>
#include <functional>
#include <assert.h>
using namespace std;
using ll = long long;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	ll n, m;
	cin >> n >> m;
	ll foo;
	for (ll i = 0; i < 2*n; i++) cin >> foo;

	vector<vector<ll>> adj(2*n);
	vector<ll> deg(2*n);
	for (ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		a--; b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
		deg[a]++; deg[b]++;
	}

	vector<ll> odds;
	ll N = n;
	for (ll i = 0; i < n; i++) if (deg[i] & 1) odds.push_back(i);
	for (ll i = 0; i < (ll) odds.size(); i += 2) {
		deg[odds[i]]++;
		deg[odds[i+1]]++;
		deg[N] = 2;
		adj[odds[i]].push_back(N);
		adj[odds[i+1]].push_back(N);
		adj[N].push_back(odds[i]);
		adj[N++].push_back(odds[i+1]);
	}

	map<pair<ll, ll>, bool> pc;
	deque<ll> tour;
	function<void(ll)> dfs = [&](ll v) {
		for (ll nxt: adj[v]) if (!pc[make_pair(v, nxt)]) { // quadratic for large star shaped graphs
			pc[make_pair(v, nxt)] = pc[make_pair(nxt, v)] = true;
			deg[v]--;
			deg[nxt]--;
			dfs(nxt);
		}
		tour.push_back(v < n ? v : -1);
	};

	vector<vector<ll>> res;
	for (ll v = 0; v < n; v++) {
		if (deg[v] == 0) continue;
		dfs(v);
		assert (tour[0] == tour.back());

		auto mo = find(tour.begin(), tour.end(), -1LL);
		if (mo != tour.end())
			tour.pop_back(); // destroy the cycle
		else
			tour.push_front(-1); // found a cycle

		while (tour[0] != -1) {
			// first and last paths are split
			tour.push_back(tour[0]);
			tour.pop_front();
		}

		for (ll v: tour) {
			if (v == -1) res.push_back({});
			else res.back().push_back(v);
		}
		tour.clear();
	}

	cout << res.size() << '\n';
	for (auto &v: res) {
		cout << v.size() << '\n';
		for (ll k: v) cout << k+1 << ' ';
		cout << '\n';
	}

	return 0;
}
