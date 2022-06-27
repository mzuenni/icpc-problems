#include <bits/stdc++.h>
using namespace std;

vector<int> matching_nxt;
vector<bool> used;
vector<vector<int>> graph;

bool dfs(int v) {
	if (used[v]) return false;
	used[v] = true;
	for (int u: graph[v]) {
		if (matching_nxt[u] == -1 || dfs(matching_nxt[u])) {
			matching_nxt[u] = v;
			return true;
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	const int nax = 2 * 10000000 + 1;
	vector<bool> is_prime(nax, true);
	is_prime[0] = is_prime[1] = false;
	for (long long i = 2; i < nax; i++) if (is_prime[i]) {
		for (long long j = i * i; j < nax; j += i) is_prime[j] = false;
	}

	int n; cin >> n;
	vector<int> a(n);
	for (auto &k: a) cin >> k;

	vector<int> odd, even;
	bool seen_one = false;
	for (int k: a) {
		if (k % 2 == 0)
			even.push_back(k);
		else {
			if (k != 1 || !seen_one) odd.push_back(k);
			if (k == 1) seen_one = true;
		}
	}

	n = (int) odd.size() + (int) even.size();
	matching_nxt.assign(n, -1);
	graph.resize(n);

	for (int i = 0; i < (int) odd.size(); i++) for (int j = 0; j < (int) even.size(); j++) {
		if (is_prime[odd[i] + even[j]]) {
			graph[i].push_back(j + (int) odd.size());
			graph[j + (int) odd.size()].push_back(i);
		}
	}

	for (int v = 0; v < (int) odd.size(); v++) {
		used.assign(n, false);
		dfs(v);
	}

	int res = 0;
	for (int i = 0; i < n; i++) res += matching_nxt[i] == -1;
	
	cout << res << '\n';
	return 0;
}
