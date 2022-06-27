#include<bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll n = 100000;
constexpr ll extraDeg = n-137;
constexpr ll seed = 127832198;
mt19937 rng(seed);

void print(vector<pair<ll, ll>> edges) {
	vector<ll> perm(n);
	for (ll i = 0; i < n; i++) perm[i] = i;
	shuffle(all(perm), rng);
	cout << n << " " << sz(edges) << endl;
	shuffle(all(edges), rng);
	for (auto e : edges) {
		e.first = perm[e.first];
		e.second = perm[e.second];
		if (e.first > e.second) swap(e.first, e.second);
		assert(e.first != e.second);
		cout << e.first+1 << " " << e.second+1 << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<pair<ll, ll>> edges;
	for (ll i = 1; i+1 < n; i++) edges.push_back({i, i+1});
	vector<ll> perm(n-1);
	for (ll i = 0; i + 1 < n; i++) perm[i] = i + 1;
	shuffle(all(perm), rng);
	assert(sz(perm) >= extraDeg);
	for (ll i = 0; i < extraDeg; i++) {
		edges.push_back({0, perm[i]});
	}
	print(edges);
}
