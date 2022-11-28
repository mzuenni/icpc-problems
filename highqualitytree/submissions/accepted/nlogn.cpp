#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

vector<vector<ll>> adj;

ll dfs(ll c, ll prev, vector<ll>& right) {
	ll active = 0;
	vector<ll> left;
	int child = 0;
	for (ll x : adj[c]) {
		if (x == prev) continue;
		if (child == 0)	active += dfs(x, c, right);
		if (child == 1)	active += dfs(x, c, left);
		child++;
	}
	assert(child <= 2);
	if (sz(left) > sz(right)) swap(left, right);
	while (sz(right) > sz(left) + 1) {
		active -= right.back();
		right.pop_back();
	}
	for (ll i = 0; i < sz(left); i++) right[i] += left[i];
	right.insert(right.begin(), 1);
	active++;
	return active;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	adj.assign(n, {});
	for (ll i = 1; i < n; i++) {
		ll a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	vector<ll> tmp;
	cout << n-dfs(0, -1, tmp) << endl;
}
