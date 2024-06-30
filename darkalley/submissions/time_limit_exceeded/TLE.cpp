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


struct slow {
    vector<ll> data;
    ll mul;
    slow(ll n, ll mul) : data(n), mul(mul) {}
    void update(ll pos, ll light) {
        for (ll i = 0; i < sz(data); i++) {
            data[i] += light * powMod(mul, abs(pos - i));
            data[i] %= mod;
        }
    }
    ll get(ll pos) {
        return data[pos];
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
	slow sol(n, pp);
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
