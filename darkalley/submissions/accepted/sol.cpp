#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll mod = 1e9+7;

ll powMod(ll a, ll b = mod - 2, ll n = mod) {
	ll res = 1;
	while (b > 0) {
		if (b & 1) res = (a * res) % n;
		a = (a * a) % n;
		b /= 2;
	}
	return res;
}


struct FT {
	vector<ll> tree;

	void update(int i, ll val) {
		for (i++; i < sz(tree); i += (i & (-i))) {
			tree[i] += val;
			tree[i] %= mod;
		}
	}

	FT(int n) {
		tree.assign(n + 1,0);
	}

	ll prefix_sum(int i) {
		ll sum = 0;
		for (i++; i > 0; i -= (i & (-i))) sum += tree[i];
		return sum % mod;
	}

};

struct fast {
	FT lr, rl;
	ll n, mul, div;
	fast(ll n, ll mul) : lr(n), rl(n), n(n), mul(mul), div(powMod(mul)) {}
	void update(ll pos, ll light) {
		rl.update(n - pos, light*powMod(div, n - 1 - pos));
		lr.update(pos, light*powMod(div, pos));
	}
	ll get(ll pos) {
		return  rl.prefix_sum(n - 1 - pos) * powMod(mul, n - 1 - pos) +
				lr.prefix_sum(pos) * powMod(mul, pos);
	}
};

constexpr ll decimals = 1000000;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, q;
	ld p;
	cin >> n >> q >> p;
	ll pp = ((decimals - (ll)round(p*decimals)) * powMod(decimals)) % mod;
	fast sol(n, pp);
	for (ll i = 0; i < q; i++) {
		char type;
		cin >> type;
		if (type == '+') {
			ll b, x;
			cin >> b >> x;
			sol.update(x - 1, b);
		} else if (type == '-') {
			ll b, x;
			cin >> b >> x;
			sol.update(x - 1, mod-b);
		} else {
			ll x;
			cin >> x;
			cout << sol.get(x - 1) % mod << "\n";
		}
	}
}
