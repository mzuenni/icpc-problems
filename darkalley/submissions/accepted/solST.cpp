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


constexpr ll query_default = 0;
struct ST {
    vector<ll> tree;

    ll combine(ll a, ll b) {
        return (a + b) % mod;
    }

    ST(int n) {
        tree.assign(n*2, query_default);
    }

    void modify(int l, int r, ll value) {
        for (l += sz(tree)/2, r += sz(tree)/2; l < r; l /= 2, r /= 2) {
            if (l&1) {tree[l] = combine(tree[l], value); l++;};
            if (r&1) {--r; tree[r] = combine(value, tree[r]);};
    }}

    ll query(int p) {
        ll res = query_default;
        for (p += sz(tree)/2; p > 0; p = p/2) {
            res = combine(res, tree[p]);
        }
        return res;
    }

};

struct fast {
	ST lr, rl;
	ll n, mul, div;
	fast(ll n, ll mul) : lr(n), rl(n), n(n), mul(mul), div(powMod(mul)) {}
	void update(ll pos, ll light) {
		rl.modify(0, pos, light*powMod(div, n - 1 - pos));
        lr.modify(pos, n, light*powMod(div, pos));
	}
	ll get(ll pos) {
		return  rl.query(pos) * powMod(mul, n - 1 - pos) +
                lr.query(pos) * powMod(mul, pos);
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
