#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int foo;
    for (int i = 0; i < 2*n; i++) {
        cin >> foo;
    }

    vector<vector<int>> adj(n);
    vector<int> edge_xor(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(i);
        adj[b].push_back(i);
        edge_xor[i] = a ^ b;
    }

    vector<int> odds;
    for (int i = 0; i < n; i++) {
        if (ssize(adj[i]) % 2 == 1) {
            odds.push_back(i);
        }
    }
    for (int i = 0; i < ssize(odds); i += 2) {
        int a = odds[i], b = odds[i+1];
        adj[a].push_back(m + i/2);
        adj[b].push_back(m + i/2);
        edge_xor.push_back(a ^ b);
    }

    vector<int> ptr(n), mark(size(edge_xor));
    auto dfs = [&](const auto &self, int i, vector<int> &edges) -> void {
        while (ptr[i] < ssize(adj[i])) {
            int k = adj[i][ ptr[i]++ ];
            if (mark[k]) continue;
            mark[k] = 1;
            self(self, edge_xor[k] ^ i, edges);
            edges.push_back(k);
        }
    };

    vector<vector<int>> paths;
    auto add = [&](int i) {
        vector<int> edges;
        dfs(dfs, i, edges);

        vector<vector<int>> segments;
        segments.push_back({i});

        for (int k: edges) {
            if (k >= m) segments.push_back({});
            i ^= edge_xor[k];
            segments.back().push_back(i);
        }

        if (ssize(segments) == 1) {
            paths.push_back(segments[0]);
        } else {
            copy(begin(segments[0])+1, end(segments[0]), back_inserter(segments.back()));
            copy(begin(segments)+1, end(segments), back_inserter(paths));
        }
    };

    for (int i = 0; i < n; i++) {
        if (ptr[i] < ssize(adj[i])) add(i);
    }
    
    cout << size(paths) << '\n';
    for (auto path: paths) {
        cout << size(path) << '\n';
        for (int i: path) cout << i+1 << ' ';
        cout << '\n';
    }
}
