#include<bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll seed = 127832198;
mt19937 rng(seed);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, m;
	cin >> n >> m;
	vector<pair<ll, ll>> edges;
	for (ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		edges.push_back({a, b});
	}
	shuffle(all(edges), rng);
	cout << n << " " << m << endl;
	for (auto e : edges) {
		cout << e.first << " " << e.second << endl;
	}
}
