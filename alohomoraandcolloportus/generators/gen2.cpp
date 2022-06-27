#include<bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll n = 100000;
constexpr ll seed = 987654321;
constexpr ld triangle = 0.5;
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
	vector<ll> deg(n);
	deque<ll> todo = {0};
	ll next = 1;
	while (next < n && !todo.empty()) {
		swap(todo[0], todo[uniform_int_distribution<ll>(0, sz(todo)-1)(rng)]);
		ll x = todo.front();
		todo.pop_front();
		if (deg[x] == 2 || next + 1 == n) {
			deg[x]++;
			deg[next]++;
			todo.push_back(next);
			edges.push_back({x, next});
			next++;
		} else {
			deg[x]++;
			deg[next]++;
			deg[next+1]++;
			edges.push_back({x, next});
			edges.push_back({x, next+1});
			if (uniform_real_distribution<ld>(0, 1)(rng) < triangle) {
				deg[next]++;
				deg[next+1]++;
				edges.push_back({next, next+1});
			}
			todo.push_back(next);
			todo.push_back(next+1);
			next += 2;
		}
	}
	for (ll i = 0; i < n; i++) {

	}
	print(edges);
}
