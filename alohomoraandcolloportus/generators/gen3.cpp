#include<bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll n = 100000;
constexpr ll seed = 123456789;
constexpr ld split = 0.5;
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
	deque<ll> leaves = {0};
	vector<ll> deg2;
	ll next = 1;
	while (next < n && !leaves.empty()) {
		swap(leaves[0], leaves[uniform_int_distribution<ll>(0, sz(leaves)-1)(rng)]);
		ll x = leaves.front();
		leaves.pop_front();

		edges.push_back({x, next});
		leaves.push_back(next);
		next++;
		if (next < n && uniform_real_distribution<ld>(0, 1)(rng) < split) {
			edges.push_back({x, next});
			leaves.push_back(next);
			next++;
		} else {
			deg2.push_back(next);
		}
	}
	for (ll x : leaves) deg2.push_back(x);
	shuffle(all(deg2), rng);
	for (ll i = 1; i < sz(deg2); i += 2) {
		edges.push_back({deg2[i], deg2[i-1]});
	}
	print(edges);
}
