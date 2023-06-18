#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

constexpr int maxW = 20;
struct perm {
	array<int, maxW> data;
	perm(int a = 0, int b = 0) {
		for (int i = 0; i < maxW; i++) data[i] = i;
		swap(data[a], data[b]);
	}
	perm operator()(const perm& o) const {
		perm res;
		for (int i = 0; i < maxW; i++) res.data[i] = data[o.data[i]];
		return res;
	}
	int swaps() const {
		int res = maxW;
		bitset<maxW> seen;
		for (int i = 0; i < maxW; i++) {
			if (!seen[i]) {
				res--;
				int c = i;
				while (!seen[c]) {
					seen[c] = true;
					c = data[c];
				}
			}
		}
		return res;
	}
};

vector<ll> brute(ll h, const vector<pair<ll, ll>>& in) {
	vector<ll> res(sz(in));
	map<ll, ll> swaps;
	for (ll i = 0; i < sz(in); i++) {
		auto it = swaps.find(in[i].first);
		if (it == swaps.end()) {
			swaps[in[i].first] = in[i].second;
		} else {
			swaps.erase(it);
		}
		perm p;
		for (auto e : swaps) {
			swap(p.data[e.second], p.data[e.second + 1]);
		}
		res[i] = p.swaps();
	}
	return res;
}



int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll w, h, q;
	cin >> w >> h >> q;
	vector<pair<ll, ll>> in(q);
	for (ll i = 0; i < q; i++) {
		ll y, x1, x2;
		cin >> y >> x1 >> x2;
		y--;
		x1--;
		x2--;
		in[i] = {y, min(x1, x2)};
	}
	auto res = brute(h, in);
	for (ll x : res) {
		cout << x << "\n";
	}
}
