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

	vector<int> v(n);
	iota(begin(v), end(v), 0);
	sort(begin(v), end(v), [&](int i, int j) { return size(adj[i]) < size(adj[j]); });

	vector<int> pos(n);
	for (int i = 0; i < n; i++) {
		pos[v[i]] = i;
	}

	vector<int> mark(n,-1), par(n,-1), dist(n), q(n);
	int res = 5;
	for (int s: v) {
		int qh = 0, qt = 1;
		dist[s] = 0, mark[s] = s, q[0] = s;
		while (qh < qt) {
			int i = q[qh++];
			if (dist[i] >= 3) break;
			for (int j: adj[i]) {
				if (pos[j] < pos[s]) continue;
				if (mark[j] == s) {
					if (j == par[i]) continue;
					int cur = dist[i]+dist[j]+1;
					res = min(res,cur);
				} else {
					dist[j] = dist[i]+1, par[j] = i, mark[j] = s, q[qt++] = j;
				}
			}
		}
	}
	cout << res << '\n';
}
