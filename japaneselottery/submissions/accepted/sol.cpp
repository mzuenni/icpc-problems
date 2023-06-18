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

struct st {
	vector<perm> tree;

	perm combine(perm a, perm b) {
		return a(b);
	}

	st(int n) : tree(2*n) {}

	void update(int p, perm value) {
		p += sz(tree)/2;
		tree[p] = tree[p](value);
		for (p /= 2; p > 0; p /= 2) {
			tree[p] = combine(tree[2*p], tree[2*p+1]);
	}}

	perm query(int l, int r) {
		perm resL, resR;
		for (l += sz(tree)/2, r += sz(tree)/2; l < r; l /= 2, r /= 2) {
			if (l&1) resL = combine(resL, tree[l++]);
			if (r&1) resR = combine(tree[--r], resR);
		}
		return combine(resL, resR);
	}
};

vector<ll> solve(ll h, const vector<pair<ll, ll>>& in) {
	st tree(h);
	vector<ll> res(sz(in));
	for (ll i = 0; i < sz(in); i++) {
		tree.update(in[i].first, perm(in[i].second, in[i].second + 1));
		res[i] = tree.query(0, h).swaps();
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
	auto res = solve(h, in);
	for (ll x : res) {
		cout << x << "\n";
	}
}
