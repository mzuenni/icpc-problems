#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

ll res = 5;
vector<vector<ll>> adj;
vector<ll> dist;

void dfs(ll c = 0, ll prev = -1, ll d = 0) {
	if (dist[c] >= 0) {
		res = min(res, d + dist[c]);
	} else {
		dist[c] = d;
		for (ll x : adj[c]) {
			if (x == prev) continue;
			dfs(x, c, d + 1);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, m;
	cin >> n >> m;
	ll trash;
	for (ll i = 0; i < 2*n; i++) cin >> trash;
	adj.assign(n, {});
	for (ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dist.assign(n, -1);
	for (ll i = 0; i < n; i++) {
		if (dist[i] < 0) dfs(i);
	}
	cout << res << endl;
}
