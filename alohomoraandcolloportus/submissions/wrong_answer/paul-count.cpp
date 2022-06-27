#include <bits/stdc++.h>
using namespace std;

int path_length(vector<vector<int>> adj, int k) {
	for (auto &v: adj) {
		auto it = find(begin(v), end(v), k);
		if (it != end(v)) v.erase(it);
	}
	adj[k].clear();

	int i = 0;
	while (size(adj[i]) != 1) i++;

	int j = adj[i][0], len = 2;
	while (size(adj[j]) == 2) {
		i ^= adj[j][0] ^ adj[j][1];
		swap(i,j);
		len++;
	}
	return len;
}

bool solve() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> adj(n);
	while (m--) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	vector<int> deg(n), cnt(n+1);
	for (int i = 0; i < n; i++) {
		deg[i] = size(adj[i]);
		cnt[deg[i]]++;
	}
	
	auto change_degree = [&](int i, int d) {
		cnt[deg[i]]--;
		deg[i] += d;
		cnt[deg[i]]++;
	};

	auto change_vertex = [&](int i, int s) {
		change_degree(i, s*size(adj[i]));
		for (int j: adj[i]) change_degree(j, s);
	};

	for (int i = 0; i < n; i++) {
		change_vertex(i, -1);

		if (cnt[1] == 2 && cnt[2] == n-3) {
			return path_length(adj,i) == n-1;
		}

		change_vertex(i, 1);
	}
	
	return false;
}

int main() {
	cout << (solve() ? "yes" : "no") << endl;
}
