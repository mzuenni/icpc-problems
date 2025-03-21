#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),(a).end()

int main() {
	int n, m;
	cin >> n >> m;
	for (int t, i = 0; i < 2 * n; i++) cin >> t;
	vector<vector<pair<int, int>>> adj(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].emplace_back(b, i), adj[b].emplace_back(a, i);
	}

	int m2 = m;
	vector<bool> odd(n);
	for (int pre = -1, i = 0; i < n; i++) {
		if (not (odd[i] = sz(adj[i]) % 2))
			continue;
		if (pre < 0) pre = i;
		else {
			adj[pre].emplace_back(i, m2);
			adj[i].emplace_back(pre, m2);
			m2++, pre = -1;
		}
	}
	for (int i = 0; i < n; i++) reverse(all(adj[i]));

	vector<vector<int>> res;
	vector<bool> remaining(m2, true);
	const auto drop = [&](int i) {
		while (not adj[i].empty() and not remaining[adj[i].back().second])
			adj[i].pop_back();
		return adj[i].empty();
	};
	const auto dfs = [&](auto&& self, int i) -> void {
		while (not drop(i)) {
			auto[j,e] = adj[i].back();
			remaining[e] = false;
			self(self, j);
			if (e >= m) res.emplace_back();
		}
		res.back().emplace_back(i);
	};
	for (int k = 0; k < 2; k++)
		for (int i = 0; i < n; i++) {
			if (drop(i) or (k==0 and not odd[i]))
				continue;
			res.emplace_back();
			dfs(dfs, i);
		}
	res.erase(remove_if(all(res), [](auto&v) { return sz(v) < 2; }), res.end());
	cout << sz(res) << '\n';
	for (auto& v : res) {
		cout << sz(v) << '\n';
		for (auto x : v)
			cout << x+1 << ' ';
		cout << '\n';
	}
}
