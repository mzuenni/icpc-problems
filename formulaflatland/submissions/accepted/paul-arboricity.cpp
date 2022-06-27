// Based on the algorithms C3 and C4 found in
//
// Norishige Chiba and Takao Nishizeki. "Arboricity and subgraph listing
// algorithms." SIAM Journal on computing 14.1 (1985): 210-223.

#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	vector<pair<int,int>> p(n);
	for (auto &[x,y]: p) cin >> x >> y;

	vector<vector<int>> adj(n);
	while (m--) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	vector<int> deg(n);
	for (int i = 0; i < n; i++) {
		deg[i] = size(adj[i]);
	}

	vector<int> v(n);
	iota(begin(v), end(v), 0);
	sort(begin(v), end(v), [&](int a, int b) { return deg[a] > deg[b]; });

	int res = 5;
	vector<int> del(n), mark1(n), mark2(n);
	for (int a: v) {
		del[a] = 1;
		for (int b: adj[a]) if (!del[b]) {
			mark1[b]++;
			if (mark2[b]) res = min(res,3);
			for (int c: adj[b]) if (!del[c]) {
				if (mark1[c]) res = min(res,3);
				if (++mark2[c] > 1) res = min(res,4);
			}
		}
		for (int b: adj[a]) if (!del[b]) {
			mark1[b]--;
			for (int c: adj[b]) if (!del[c]) {
				mark2[c]--;
			}
		}
	}
	cout << res << '\n';
}
