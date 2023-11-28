#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll inf = 0x3FFFFFFFFFFF;

ll gcd(ll a, ll b) {return b == 0 ? a : gcd(b, a % b);}

// a*x + b*y = ggt(a, b)
ll extendedEuclid(ll a, ll b, ll& x, ll& y) {
	if (a == 0) {x = 0; y = 1; return b;}
	ll x1, y1, d = extendedEuclid(b % a, a, x1, y1);
	x = y1 - (b / a) * x1; y = x1;
	return d;
}


ll multInv(ll n, ll p) {
	ll x, y;
	extendedEuclid(n, p, x, y); // Implementierung von oben.
	return ((x % p) + p) % p;
}

ll n, q;

pair<ll, ll> combine(ll i, pair<ll, ll> a, pair<ll, ll> b) {
	if (a.first == inf) return b;
	if (b.first == inf) return a;
	ll da = i-a.second;
	if (da < 0) da += n;
	ll db = i-b.second;
	if (db < 0) db += n;
	if (da < db) return a;
	return b;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> q;
	vector<pair<ll, ll>> state(n);
	for (ll i = 0; i < n; i++) state[i] = {i, i};
	state[0].first = n;
	for (ll i = 0; i < q; i++) {
		char type;
		ll x;
		cin >> type >> x;
		if (type == '+') {
			vector<pair<ll, ll>> old(n, {inf, 0});
			swap(old, state);
			for (ll i = 0; i < n; i++) {
				old[i].second = i;
				state[(i+x)%n] = combine((i+x)%n, state[(i+x)%n], old[i]);
			}
		} else if (type == '*') {
			vector<pair<ll, ll>> old(n, {inf, 0});
			swap(old, state);
			for (ll i = 0; i < n; i++) {
				old[i].second = i;
				state[(i*x)%n] = combine((i*x)%n, state[(i*x)%n], old[i]);
			}
		} else {
			ll y = state[x % n].first;
			if (y == inf) y = -1;
			cout << y << endl;
		}
	}
}
