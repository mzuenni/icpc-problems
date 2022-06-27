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

	vector<int> q(n);
	int qh = 0, qt = 0;
	for (int i = 0; i < n; i++) {
		if (deg[i] <= 5) {
			q[qt++] = i;
		}
	}
	while (qh < qt) {
		int i = q[qh++];
		for (int j: adj[i]) {
			if (deg[j]-- == 6) q[qt++] = j;
		}
	}

	vector<int> pos(n);
	for (int i = 0; i < n; i++) {
		pos[q[i]] = i;
	}

	vector<vector<int>> succ(n);
	for (int i = 0; i < n; i++) {
		for (int j: adj[i]) {
			if (pos[i] < pos[j]) succ[i].push_back(j);
		}
	}
	
	int res = 5;
	vector<int> mark1(n), mark2(n);
	vector<pair<int,int>> pairs;
	for (int a = 0; a < n; a++) {
		for (int b: succ[a]) {
			mark1[b]++;
			for (int c: succ[b]) {
				mark2[c]++;
			}
		}
		for (int b: succ[a]) {
			if (mark2[b]) res = min(res,3);
			for (int c: succ[b]) {
				if (mark2[c] > 1) res = min(res,4);
				for (int d: succ[c]) {
					if (mark1[d]) res = min(res,4);
				}
			}
			for (int bb: succ[a]) {
				if (b < bb) pairs.emplace_back(b,bb);
			}
		}		
		for (int b: succ[a]) {
			mark1[b]--;
			for (int c: succ[b]) {
				mark2[c]--;
			}
		}		
	}
	
	sort(begin(pairs), end(pairs));
	if (unique(begin(pairs), end(pairs)) != end(pairs)) {
		res = min(res,4);
	}

	cout << res << '\n';
}
