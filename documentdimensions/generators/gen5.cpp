#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll n = 1000000;
constexpr ll minWS = 1;
constexpr ll maxWS = 5;
constexpr ll minWB = 100;
constexpr ll maxWB = 200;
constexpr ll seed = 146328;

mt19937 rng(seed);
ll getRandom(ll l, ll r) {
	return uniform_int_distribution<ll>(l, r-1)(rng);
}
string getRandomString(ll l) {
	string res(l, 'a');
	for (char& c : res) c = (char)getRandom('a', 'z' + 1);
		return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<ll> data;
	ll sum = 0;
	while (sum < n) {
		ll x = getRandom(minWB, maxWB);
		sum += x;
		data.push_back(x);
		ll csum = 0;
		while (csum < x) {
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
	cout << sz(data) << endl;
	for (ll i = 0; i < sz(data); i++) {
		cout << getRandomString(data[i]);
		if (i + 1 != sz(data)) cout << " ";
	}
	cout << endl;
	cerr << sum << endl;
}
