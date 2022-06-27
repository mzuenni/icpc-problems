#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll sigma = 26;
constexpr ll limn = 150000;
constexpr ll seed = 123456789;

mt19937 rng(seed);
ll random(ll l, ll r) {
	return uniform_int_distribution<ll>(l, r-1)(rng);
}

string genString(ll l) {
	string res(l, '*');
	for (char& c : res) c = random(0, sigma) + 'a';
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << limn << endl;
	cout << genString(limn) << endl;
	cout << genString(limn) << endl;
}
