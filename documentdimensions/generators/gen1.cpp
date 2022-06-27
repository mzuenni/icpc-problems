#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll n = 1000000;
constexpr ll minW = 100 - 25;
constexpr ll maxW = 100 + 25;
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


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<string> data;
	ll sum = 0;
	while (sum < n) {
		ll x = min(n - sum, getRandom(minW, maxW));
		sum += x;
		data.push_back(getRandomString(x));
	}

	shuffle(all(data), rng);
	cout << sz(data) << endl;
	for (ll i = 0; i < sz(data); i++) {
		cout << data[i];
		if (i + 1 != sz(data)) cout << " ";
	}
	cout << endl;
}
