#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll n = 1000000;
constexpr ll minWS = 2;
constexpr ll maxWS = 5;
constexpr ll minWB = 100;
constexpr ll maxWB = 200;
constexpr ll tries = 1000;
constexpr ll seed = 123456789;
//200 900
mt19937 rng(seed);
ll getRandom(ll l, ll r) {
	return uniform_int_distribution<ll>(l, r-1)(rng);
}
string getRandomString(ll l) {
	string res(l, 'a');
	for (char& c : res) c = (char)getRandom('a', 'z' + 1);
	return res;
}

constexpr ll inf = 0x3FFFFFFFFFFFFFFF;

ll solve(const vector<ll>& in) {
	vector<ll> pref = {0};
	ll ma = 1;
	for (ll x : in) {
		pref.push_back(pref.back() + x + 1);
		ma = max(ma, x + 1);
	}
	vector<ll> inv(2*pref.back() + 5, 0);
	for (ll i = 0; i < sz(pref); i++) inv[pref[i]] = i;
	for (ll i = 1; i < sz(inv); i++) {
		inv[i] = max(inv[i], inv[i - 1]);
	}
	ll res = inf;
	ll rl = -1;
	for (ll l = ma; l <= pref.back(); l++) {
		ll rows = 0;
		ll realL = 0;
		for (ll i = 0; i < sz(in); rows++) {
			ll lim = pref[i] + l;
			i = inv[lim];
			realL = max(realL, pref[i] - (lim - l));
		}
		ll c = 2*(realL - 1 + rows);
		if (c < res) {
			res = c;
			rl = l - ma;
		}
	}
	return rl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	while (true) {
		vector<ll> data;
		ll sum = 0;
		while (sum < n) {
			ll x = getRandom(minWB, maxWB);
			sum += x;
			data.push_back(x);
			ll csum = 0;
			while (5*csum < x) {
				ll y = getRandom(minWS, maxWS);			
				sum += y;
				csum += y;
				data.push_back(y);
			}
		}
		shuffle(all(data), rng);
		while (sum > n) {
			sum -= data.back();
			data.pop_back();
		}

		auto res = solve(data);
		if (res > tries) {
			cerr << res << endl;
			cout << sz(data) << endl;
			for (ll i = 0; i < sz(data); i++) {
				cout << getRandomString(data[i]);
				if (i + 1 != sz(data)) cout << " ";
			}
			cout << endl;
			return 0;
		}
	}
}
