#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <set>

using namespace std;

using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;

constexpr ll oo = 0x3f3f3f3f3f3f3f3fLL;

#define sz(a) ll((a).size())
#define all(a) (a).begin(),(a).end()

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

	ll n,m;
	cin >> n >> m;

	// throw away positions
	for (ll i = 0, x; i < n; i++) cin >> x >> x;

	vector<vll> adj(n);

	while (m-- > 0) {
		ll a,b;
		cin >> a >> b;
		adj[--a].emplace_back(--b);
		adj[b].emplace_back(a);
	}

	// orientate edges
	{
		vll q, deg(n);
		for (ll i = 0; i < n; i++)
			if((deg[i] = sz(adj[i])) <= 5)
				q.emplace_back(i);
		for (ll ii = 0; ii < n; ii++) {
			const ll i = q[ii];
			copy_if(all(adj[i]), back_inserter(q), [&](ll j) { return deg[j] > 0 && --deg[j] == 5; });
			adj[i].erase(remove_if(all(adj[i]), [&](ll j) { return deg[j] == -1; }), adj[i].end());
			sort(all(adj[i]));
			deg[i] = -1;
		}
	}

	ll res = 5;

	vll dist(n, oo);
	for (ll i = 0; i < n; i++) {
		vll vis;
		function<void(ll,ll)> dfs = [&](ll j, ll d) {
			if (dist[j] < oo)
				res = min(res, dist[j] + d);
			else
				vis.emplace_back(j);
			dist[j] = min(dist[j], d);
			if (d + 1 >= res) return;
			for (ll k : adj[j]) dfs(k, d+1);
		};
		dfs(i, 0);
		for (ll j : vis) dist[j] = oo;
	}

	// test for diamond
	if (res > 4) {
		 vector<set<ll>> star2(n);
		 for (ll i = 0; i < n; i++)
		 	for (ll j = 0; j < sz(adj[i]); j++)
		 		for (ll k = 0; k < j; k++)
		 			if (!star2[ adj[i][j] ].emplace(adj[i][k]).second) {
		 				cout << 4 << endl;
		 				return 0;
		 			}
	}

	cout << res << endl;

	return 0;
}
