#include <bits/stdc++.h>
using namespace std;

#define sz(x) (ll) (x).size()
#define all(x) (x).begin(), (x).end()

using ll = long long;
using ld = long double;

ll gcd(ll a, ll b) {return b == 0 ? a : gcd(b, a % b);}

// a*x + b*y = ggt(a, b)
ll extendedEuclid(ll a, ll b, ll& x, ll& y) {
	if (a == 0) {x = 0; y = 1; return b;}
	ll x1, y1, d = extendedEuclid(b % a, a, x1, y1);
	x = y1 - (b / a) * x1; y = x1;
	return d;
}


ll mod, q;
ll a = 1;
ll b = 0; // x -> a*x + b

//works with any combine function
pair<ll, ll> combine(ll i, pair<ll, ll> a, pair<ll, ll> b) {
	if (a.first < 0) return b;
	if (b.first < 0) return a;
	ll da = i-a.second;
	if (da < 0) da += mod;
	ll db = i-b.second;
	if (db < 0) db += mod;
	if (da < db) return a;
	return b;
}

ll getPos(ll x) {
	ll y = (x - b + mod) % mod;
	ll v, w;
	ll g = extendedEuclid(a, mod, v, w);
	ll res = ((((y / g) * v) % mod + mod) % mod) % (mod / g);
	return res;
}

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> mod >> q;
	vector<ll> state(mod);
	for (ll i = 0; i < mod; i++) state[i] = i;
	state[0] = mod;
	ll active = mod;
	for (ll _ = 0; _ < q; _++){
		char c;
		ll x;
		cin >> c >> x;
		if(c == '+'){
			b = (b + x) % mod;
		} else if (c == '*'){
			ll g = gcd(x, active);
			if (g != 1) {
				// handle collisions
				active /= g;
				// moves[i] should contain all persons moving to chair
				vector<vector<pair<ll, ll>>> moves(mod);
				for (ll i = 0; i < mod; i++) {
					ll y = (i - b + mod) % mod;
					if (gcd(y, mod) % gcd(a, mod) == 0) {
						//res is person at i, and moves to i*x?
						moves[(i*x)%mod].push_back({state[getPos(i)], i});
					}
				}
				b = (b * x) % mod;
				a = (a * x) % mod;
				for (ll i = 0; i < mod; i++) {
					if (moves[i].empty()) continue;
					pair<ll, ll> tmp = moves[i][0];
					for (auto e : moves[i]) {
						tmp = combine(i, tmp, e);
					}
					state[getPos(i)] = tmp.first;
				}
			} else {
				b = (b * x) % mod;
				a = (a * x) % mod;
			}
		} else {
			ll y = (x - b + mod) % mod;
			if (gcd(y, mod) % gcd(a, mod) != 0) cout << -1 << endl;
			else cout << state[getPos(x)] << endl;
		}
	}   

}

