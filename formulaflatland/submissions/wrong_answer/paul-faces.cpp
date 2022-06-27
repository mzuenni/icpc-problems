#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct point { i64 x, y; };

point operator-(point a, point b) {
	return {a.x-b.x, a.y-b.y};
}

bool operator<(point a, point b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

i64 operator%(point a, point b) {
	return a.x*b.y - a.y*b.x;
}

bool compare(point a, point b, point c) {
	if ((a < b) != (a < c)) {
		return (a < b) < (a < c);
	} else {
		return (b-a) % (c-a) > 0;
	}
}

template<typename T>
T other(pair<T,T> pr, T x) {
	return pr.first == x ? pr.second : pr.first;
}

int main() {
	int n, m;
	cin >> n >> m;
	
	vector<point> p(n);
	for (auto &[x,y]: p) cin >> x >> y;

	vector<vector<int>> adj(n);
	vector<pair<int,int>> edges(m);
	for (int i = 0; i < m; i++) {
		auto &[a,b] = edges[i];
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(i);
		adj[b].push_back(m+i);
	}

	vector<int> edge_pos(2*m);
	for (int a = 0; a < n; a++) {
		auto comp = [&](int i, int j) {
			int b = other(edges[i%m], a), c = other(edges[j%m], a);
			return compare(p[a], p[b], p[c]);
		};
		sort(begin(adj[a]), end(adj[a]), comp);
		for (int k = 0; k < ssize(adj[a]); k++) {
			edge_pos[ adj[a][k] ] = k;
		}
	}

	int res = 1e9;
	vector<bool> vis(2*m);
	for (int i = 0; i < 2*m; i++) if (!vis[i]) {
		int len = 0;
		while (!vis[i]) {
			vis[i] = true;
			len++;
			auto [a,b] = edges[i%m];
			if (i >= m) swap(a,b);
			int k = edge_pos[ (i+m)%(2*m) ];
			i = adj[b][ (k+1)%ssize(adj[b]) ];
		}
		res = min(res, len);
	}
	cout << res << '\n';
}

