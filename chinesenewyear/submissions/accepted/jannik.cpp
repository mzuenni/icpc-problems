#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),(a).end()

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);
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
	for (int pre = -1, i = 0; i < n; i++) {
		if (sz(adj[i]) % 2 == 0)
			continue;
		if (pre < 0) pre = i;
		else {
			adj[pre].emplace_back(i, m2);
			adj[i].emplace_back(pre, m2);
			m2++, pre = -1;
		}
	}

	vector<bool> remaining(m2, true);
	const auto drop = [&](int i) {
		while (not adj[i].empty() and not remaining[adj[i].back().second])
			adj[i].pop_back();
		return adj[i].empty();
	};
	vector<int> step;
	const auto dfs = [&](auto&& self, int i) -> void {
		while (not drop(i)) {
			auto[j,e] = adj[i].back();
			remaining[e] = false;
			self(self, j);
			if (e >= m) step.emplace_back(-1);
		}
		step.emplace_back(i);
	};
	vector<vector<int>> res;
	for (int i = 0; i < n; i++) {
		if (drop(i))
			continue;
		step.clear();
		dfs(dfs, i);
		if (auto it = find(all(step), -1); it != step.end()) {
			step.pop_back();
			rotate(step.begin(), it, step.end());
		}
		for (auto it = step.begin(), fst = it; ; it++) {
			if (it == step.end() or *it < 0) {
				if (fst != it) res.emplace_back(fst, it);
				if (it == step.end()) break;
				else fst = ++it;
			}
		}
	}
	cout << sz(res) << '\n';
	for (auto& v : res) {
		cout << sz(v) << '\n';
		for (auto x : v)
			cout << x+1 << ' ';
		cout << '\n';
	}
}
