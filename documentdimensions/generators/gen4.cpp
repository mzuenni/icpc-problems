#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll n = 577;
constexpr ll m = 1155;
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
	basic_string<ll> tmp(n, 1);
	tmp.back() = m;
	basic_string<ll> data;
	do {
		data += tmp;
	} while(next_permutation(all(tmp)));
	ll sum = 0;
	cout << sz(data) << endl;
	for (ll i = 0; i < sz(data); i++) {
		sum += data[i];
		cout << getRandomString(data[i]);
		if (i + 1 != sz(data)) cout << " ";
	}
	cout << endl;
	cerr << sum << endl;
}
