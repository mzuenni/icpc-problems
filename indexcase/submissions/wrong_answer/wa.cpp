#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

vector<vector<ll>> adj;
vector<ll> inDeg;

void init(ll n) {
	adj.assign(n, {});
	inDeg.assign(n, 0);
}

void addEdge(ll from, ll to) {
	adj[from].push_back(to);
	inDeg[to]++;
}

bool dag() {
	vector<ll> todo;
	for (ll i = 0; i < sz(adj); i++) {
		if (inDeg[i] == 0) todo.push_back(i);
	}
	ll seen = 0;
	while (!todo.empty()) {
		ll c = todo.back();
		todo.pop_back();
		seen++;
		for (ll x : adj[c]) {
			inDeg[x]--;
			if (inDeg[x] == 0) todo.push_back(x);
		}
	}
	return seen == sz(adj);
}

constexpr ll maxSigma = 100;
ll rule[maxSigma][maxSigma][maxSigma];

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
						addEdge(l, r);
					}
				}
			}
		}
	}
	cout << (!dag() ? "YES" : "NO") << endl;
}
