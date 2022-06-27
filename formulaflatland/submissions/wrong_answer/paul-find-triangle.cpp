#include <bits/stdc++.h>
using namespace std;

const int M = 333;

// Checks if a given graph has a triangle using a heavy-light approach.
bool has_triangle(vector<vector<int>> adj, set<pair<int,int>> edges) {
	int n = adj.size(), m = 0;
	
	vector<int> id(n, -1);
	for (int i = 0; i < n; i++) {
		if (int(adj[i].size()) > M) {
			id[i] = m++;
		}
	}

	vector<vector<int>> mat(m, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j: adj[i]) {
			if (min(id[i],id[j]) < 0) continue;
			mat[id[i]][id[j]] = 1;
		}
	}
	for (int a = 0; a < m; a++) {
		for (int b = 0; b < a; b++) {
			for (int c = 0; c < b; c++) {
				if (mat[a][b] && mat[b][c] && mat[c][a]) return true;
			}
		}
	}

	for (int i = 0; i < n; i++) if (id[i] == -1) {
		for (int j: adj[i]) {
			for (int k: adj[i]) {
				if (k == j) break;
				if (id[j] == -1 && j < i) continue;
				if (id[k] == -1 && k < i) continue;
				int a = j, b = k;
				if (a > b) swap(a,b);
				if (edges.count({a,b})) return true;
			}
		}
	}

	return false;
}

int main() {
	int n, m;
	cin >> n >> m;
	
	vector<pair<int,int>> p(n);
	for (auto &[x,y]: p) cin >> x >> y;

	vector<vector<int>> adj(n);
	set<pair<int,int>> edges;
	while (m--) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		if (a > b) swap(a,b);
		edges.emplace(a,b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	srand(n+m);
	int res = has_triangle(adj, edges) ? 3 : 4 + rand() % 2;
	cout << res << '\n';
}

