#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll n = 2000;
constexpr ll minW = 1;
constexpr ll maxW = 45;
constexpr ll change = 20;
constexpr ll seed = 123456789;

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

vector<pair<ll, ll>> solve(const vector<ll>& in) {
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
	vector<pair<ll, ll>> res;
	for (ll l = ma; l <= pref.back(); l++) {
		ll rows = 0;
		ll realL = 0;
		for (ll i = 0; i < sz(in); rows++) {
			ll lim = pref[i] + l;
			i = inv[lim];
			realL = max(realL, pref[i] - (lim - l));
		}
		res.push_back({l-1, 2*(realL - 1 + rows)});
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	while (true) {
		vector<ll> data;
		ll sum = 0;
		while (sum < n) {
			ll x = min(n - sum, getRandom(minW, maxW));
			sum += x;
			data.push_back(x);
		}

		shuffle(all(data), rng);
		auto res = solve(data);
		vector<ll> changes = {0};
		for (ll i = 0; i + 1 < sz(res); i++) {
			if (res[i].second < res[i + 1].second && changes.back() != 1) changes.push_back(1);
			if (res[i].second > res[i + 1].second && changes.back() != -1) changes.push_back(-1);
		}
			cerr << changes.size() << endl;
		if (changes.size() > change) {
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
