#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define size asdf

const int N = 2e5 + 10, K = 40;
vector<int> adj[N];
int size[N];
int dp[N][K];

void dfs_size(int i, int p) {
	size[i] = 1;
	for (int j: adj[i]) if (j != p) {
		dfs_size(j, i);
		size[i] += size[j];
	}
}

void dfs(int i, int p) {
	for (int j: adj[i]) if (j != p) {
		dfs(j, i);
	}
	dp[i][0] = size[i];
	dp[i][1] = size[i]-1;

	int a = 0, b = 0;
	for (int j: adj[i]) if (j != p) {
		b = j, swap(a,b);
	}

	for (int k = 2; k < K; k++) {
		for (int ka: {k-2,k-1}) {
			for (int kb: {k-2,k-1}) {
				if (max(ka,kb) != k-1) continue;
				dp[i][k] = min(dp[i][k], dp[a][ka]+dp[b][kb]);
			}
		}
	}
}

int main() {
	int n; cin >> n;
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs_size(1, 0);
	memset(dp, 0x3f, sizeof dp);
	dp[0][0] = 0;
	dfs(1, 0);
	cout << *min_element(dp[1], dp[1]+K) << '\n';
}
