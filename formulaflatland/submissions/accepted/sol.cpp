#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using Graph = vector<vector<ll>>;

// planar graphs always contain a vertex with degree <= 5
// Thus we can orientate the edges such that each vertex
// has outdegree 5 and the graph has no cycles 
// runtime O(n)
Graph orientate(const Graph& adj) {
	ll n = sz(adj);
	vector<bool> seen(n);
	vector<ll> deg(n);
	queue<ll> todo;
	for (ll i = 0; i < n; i++) {
		deg[i] = sz(adj[i]);
		assert(deg[i] > 2);
		if (deg[i] <= 5) todo.push(i);
	}
	Graph res(n);
	while (!todo.empty()) {
		ll c = todo.front();
		todo.pop();
		if (seen[c]) continue;
		seen[c] = true;
		for (ll x : adj[c]) {
			if (seen[x]) continue;
			res[c].push_back(x);
			deg[x]--;
			if (deg[x] == 5) todo.push(x);
		}
	}
	return res;
}

// since the orientate graph has no cycles we know that
// an original cycle consist of two paths between some node
// a and b. or is a diam Further, since the girth is at most 5, we only
// need to find a cycle of length 3 or 4. For a cycle of 
// length 4 the longer path can contain at most 3 edges
// (the other has to contain at leats one).
// Thus we can do a limited bfs whith max depth 3 from each vertex.
// runtime O(n*5^3)
ll solve(const Graph& adj) {
	ll n = sz(adj);
	ll res = 5;
	vector<ll> dist(n, -1);
	for (ll i = 0; i < n; i++) {
		queue<ll> todo;
		todo.push(i);
		vector<ll> done;
		dist[i] = 0;
		while (!todo.empty()) {
			ll c = todo.front();
			todo.pop();
			done.push_back(c);
			for (ll x : adj[c]) {
				if (dist[x] < 0) {
					if (dist[c] + 1 <= 3) { 
						dist[x] = dist[c] + 1;
						todo.push(x);
					}
				} else {
					res = min(res, dist[x] + dist[c] + 1);
				}
			}
		}
		for (ll x : done) dist[x] = -1;
	}
	if (res == 5) {
		set<pair<ll, ll>> seen;
		for (ll i = 0; i < n; i++) {
			for (ll j = 0; j < sz(adj[i]); j++) {
				for (ll k = 0; k < j; k++) {
					ll a = adj[i][j];
					ll b = adj[i][k];
					if (a > b) swap(a, b);
					if (seen.find({a, b}) != seen.end()) return 4;//found diam
					else seen.insert({a, b});
				}
			}
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, m;
	cin >> n >> m;
	ll trash;
	for (ll i = 0; i < 2*n; i++) cin >> trash;
	Graph adj(n);
	for (ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	adj = orientate(adj);
	cout << solve(adj) << endl;
}
