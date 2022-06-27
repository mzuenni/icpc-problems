#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

vector<vector<ll>> adj;
vector<ll> seen;
ll dfsCounter = 0;

void init(ll n) {
	adj.assign(n, {});
	seen.assign(n, 0);
}

void addEdge(ll from, ll to) {
	adj[from].push_back(to);
}

constexpr ll maxSigma = 207;
ll rule[maxSigma][maxSigma][maxSigma];

bool dfs(ll from, ll to) {
	dfsCounter++;
	vector<ll> stack = {from};
	seen[from] = dfsCounter;
	while (!stack.empty()) {
		ll c = stack.back();
		stack.pop_back();
		for (ll x : adj[c]) {
			if (x == to) {
				return true;
			} else if (seen[x] != dfsCounter) {
				seen[x] = dfsCounter;
				stack.push_back(x);
			}
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, sigma;
	cin >> n >> sigma;

	for (ll a = 0; a < sigma; a++) {
		for (ll b = 0; b < sigma; b++) {
			for (ll c = 0; c < sigma; c++) {
				cin >> rule[a][b][c];
				rule[a][b][c]--;
			}
		}
	}

	vector<ll> state(n);
	for (ll i = 0; i < n; i++) {
		cin >> state[i];
		state[i]--;
	}

	init(sigma * sigma * (n + 1));
	for (ll i = 0; i < n; i++) {
		for (ll a = 0; a < sigma; a++) {
			for (ll b = 0; b < sigma; b++) {
				for (ll c = 0; c < sigma; c++) {
					if (rule[a][b][c] == state[i]) {
						ll l = (a * sigma + b) * (n + 1) + i;
						ll r = (b * sigma + c) * (n + 1) + i + 1;
						adj[l].push_back(r);
					}
				}
			}
		}
	}
	for (ll a = 0; a < sigma; a++) {
			for (ll b = 0; b < sigma; b++) {
				ll c = (a * sigma + b) * (n + 1) + 0;
				ll d = (a * sigma + b) * (n + 1) + n;
				if (dfs(c, d)) {
					cout << "YES" << endl;
					return 0;
				}
			}
		}
	cout << "NO" << endl;
}
