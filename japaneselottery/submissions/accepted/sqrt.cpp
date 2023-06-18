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

constexpr ll maxN = 200000;
//update = blockSize;
//query = w*n/blockSize
constexpr ll blockSize = sqrt(maxW*maxN);

struct sq {
	vector<perm> blocks;
	vector<int> data;

	sq(int n) : blocks(n/blockSize + 1), data(sz(blocks) * blockSize, -1) {}

	perm update(int p, int left) {
		if (data[p] < 0) {
			data[p] = left;
		} else {
			data[p] = -1;
		}
		int b = p / blockSize;
		int l = b * blockSize;
		int r = l + blockSize;
		blocks[b] = perm();
		for (int i = l; i < r; i++) {
			if (data[i] >= 0) {
				swap(blocks[b].data[data[i]], blocks[b].data[data[i] + 1]);
			}
		}
		perm res;
		for (const auto& c : blocks) {
			res = res(c);
		}
		return res;
	}
};

vector<ll> solve(ll h, const vector<pair<ll, ll>>& in) {
	sq data(h);
	vector<ll> res(sz(in));
	for (ll i = 0; i < sz(in); i++) {
		res[i] = data.update(in[i].first, in[i].second).swaps();
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
