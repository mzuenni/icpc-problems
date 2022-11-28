#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll inf = 0x3FFFFFFFFFF;

struct seg {
	ll l, r, id;
	bool operator<(const seg& o) const {
		if (r != o.r) return r < o.r;
		return l > o.l;
	}
};

constexpr ll query_default = 0;
struct segTree {
private:
	vector<ll> tree;

	ll combine(ll a, ll b) {
		return max(a, b);
	}

public:
	segTree(ll n) : tree(2*n, query_default) {}

	void update(ll p, ll value) {
		for (tree[p += sz(tree)/2] = value, p /= 2; p > 0; p /= 2) {
			tree[p] = combine(tree[2*p], tree[2*p+1]);
	}}

	ll query(ll l, ll r) {
		ll resL = query_default;
		ll resR = query_default;
		for (l += sz(tree)/2, r += sz(tree)/2; l < r; l /= 2, r /= 2) {
			if (l&1) resL = combine(resL, tree[l++]);
			if (r&1) resR = combine(tree[--r], resR);
		}
		return combine(resL, resR);
	}
};

vector<ll> solveInner(vector<seg> in) {
	vector<ll> compressed;
	for (auto e : in) {
		compressed.push_back(e.l);
		compressed.push_back(e.r);
	}
	sort(all(compressed));
	for (auto& e : in) {
		e.l = distance(compressed.begin(), lower_bound(all(compressed), e.l));
		e.r = distance(compressed.begin(), lower_bound(all(compressed), e.r));
	}
	sort(all(in));
	vector<ll> res(sz(in));
	segTree state(sz(compressed));
	for (auto e : in) {
		ll x = state.query(e.l, e.r) + 1;
		res[e.id] = x;
		state.update(e.l, x);
	}
	return res;
}

vector<ll> solveOuter(vector<seg> in) {
	for (auto& e : in) {
		swap(e.l, e.r);
		e.r += inf;
	}
	return solveInner(in);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	vector<seg> in(n);
	for (ll i = 0; i < n; i++) {
		//assumes all (l, r) are disjoint
		ll l, length;
		cin >> l >> length;
		in[i] = {l, l + length, i};
	}
	vector<ll> res = solveOuter(in);
	for(int i = 0; i < n; ++i) cout << res[i]-1 << " \n"[i == n - 1];
}
