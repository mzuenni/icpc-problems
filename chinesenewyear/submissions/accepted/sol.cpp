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

	ll trash = 0;
	for (ll i = 0; i < 2*n; i++) cin >> trash;

	vector<multiset<pair<ll, bool>>> adj(n);
	for (ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].insert({b, true});
		adj[b].insert({a, true});
	}

	//connect odd vertices
	for (ll i = 0, last = -1; i < n; i++) {
		if (sz(adj[i]) % 2 != 0) {
			if (last < 0) {
				last = i;
			} else {
				//this can produce multi edges!
				adj[i].insert({last, false});
				adj[last].insert({i, false});
				last = -1;
			}
		}
	}

	//solve
	vector<vector<ll>> res;
	vector<ll> tmp;
	auto euler = [&](auto&& self, ll i) -> void {
		while (!adj[i].empty()) {
			auto [j, real] = *adj[i].begin();
			adj[i].erase(adj[i].begin());
			adj[j].erase(adj[j].find({i, real}));
			self(self, j);
			if (!real) tmp.push_back(-1);
		}
		tmp.push_back(i);//reversed order but we are undirected anyway
	};
	auto decompose = [&](ll i){
		if (adj[i].empty()) return;
		euler(euler, i);

		auto split = find(all(tmp), -1);
		if (split != tmp.end()) {
			tmp.pop_back();
			rotate(tmp.begin(), split, tmp.end());
			reverse(all(tmp));
			if (tmp.back() < 0) tmp.pop_back();
		}

		res.push_back({});
		for (ll x : tmp) {
			if (x < 0) {
				res.push_back({});
			} else {
				res.back().push_back(x);
			}
		}
		tmp.clear();
	};

	for (ll i = 0; i < n; i++) decompose(i);

	cout << sz(res) << endl;
	for (auto& v : res) {
		cout << sz(v) << endl;
		for (ll i = 0; i + 1 < sz(v); i++) cout << 1+v[i] << " ";
		cout << 1+v.back() << endl;
	}
}
