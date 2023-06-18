#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

constexpr int maxW = 20;
struct perm {
	array<int, maxW> data;
	perm() {
		for (int i = 0; i < maxW; i++) data[i] = i;
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

constexpr ll blockSize = 900;
//updating a block takes blockSize
//query takes h/blockSize*20
struct sq {
	vector<perm> blocks;
	vector<ll> data;

	sq(int n) : blocks((n + blockSize - 1) / blockSize), data(sz(blocks) * blockSize, -1) {}

	void update(int p, int leg) {
		if (data[p] < 0) data[p] = leg;
		else data[p] = -1;
		p /= blockSize;
		blocks[p] = perm();
		for (ll i = 0; i < blockSize; i++) {
			ll j = p * blockSize + i;
			if (data[j] >= 0) swap(blocks[p].data[data[j]], blocks[p].data[data[j]+1]);
		}
	}

	perm query() {
		perm res;
		for (auto& p : blocks) res = res(p);
		return res;
	}
};

vector<ll> solve(ll h, const vector<pair<ll, ll>>& in) {
	sq data(h);
	vector<ll> res(sz(in));
	for (ll i = 0; i < sz(in); i++) {
		data.update(in[i].first, in[i].second);
		res[i] = data.query().swaps();
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
