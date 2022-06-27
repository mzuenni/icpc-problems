#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, m;
	cin >> n >> m;
	ll trash;
	for (ll i = 0; i < 2*n; i++) cin >> trash;
	vector<vector<ll>> adj(n);
	for (ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	ll res = 5;
	for (ll i = 0; i < n; i++) {
		queue<ll> todo;
		todo.push(i);
		vector<ll> dist(n, -1);
		dist[i] = 0;
		while (!todo.empty()) {
			ll c = todo.front();
			todo.pop();
			for (ll x : adj[c]) {
				if (dist[x] < 0) {
					dist[x] = dist[c] + 1;
					todo.push(x);
				} else if (dist[x] >= dist[c]) {
					res = min(res, dist[c] + dist[x] + 1);
				}
			}
		}
	}
	cout << res << endl;
}
