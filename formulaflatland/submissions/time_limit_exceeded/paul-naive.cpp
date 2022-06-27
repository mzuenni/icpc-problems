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
	
	for (int a = 0; a < n; a++) {
		for (int b: adj[a]) if (b > a) {
			for (int c: adj[b]) if (c > a) {
				for (int d: adj[c]) {
					if (d == a) {
						cout << 3 << '\n';
						return 0;
					}
				}
			}
		}
	}

	for (int a = 0; a < n; a++) {
		for (int b: adj[a]) if (b > a) {
			for (int c: adj[b]) if (c > a) {
				for (int d: adj[c]) if (d > b) {
					for (int e: adj[d]) {
						if (e == a) {
							cout << 4 << '\n';
							return 0;
						}
					}
				}
			}
		}
	}

	cout << 5 << '\n';
}
