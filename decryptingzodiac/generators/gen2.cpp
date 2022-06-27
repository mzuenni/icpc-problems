#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll sigma = 26;
constexpr ll limn = 150000;
constexpr ll changes = 10000;
constexpr char c = 'c';
constexpr ll seed = 123456789;

mt19937 rng(seed);
ll random(ll l, ll r) {
	return uniform_int_distribution<ll>(l, r-1)(rng);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << limn << endl;
	string first(limn, c);
	for (ll i = 0; i < changes; i++) {
		ll j = random(0, limn - 1);
		first[j] = random('a', 'z');
	}
	cout << first << endl;
	string tmp(sigma, '*');
	for (ll i = 0; i < sigma; i++) tmp[i] = i + 'a';
	string tmp2;
	while (sz(tmp2) < limn) tmp2 += tmp;
	shuffle(all(tmp2), rng);
	while (sz(tmp2) > limn) tmp2.pop_back();
	cout << tmp2 << endl;
}
