#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll N = 20000007;
bitset<N / 2> isNotPrime;

bool isPrime(ll x) {
	if (x < 2 || x % 2 == 0) return x == 2;
	else return !isNotPrime[x / 2];
}

void primeSieve() {
	// i * i < N is enough for isPrime
	for (ll i = 3; i < N; i += 2) {
		if (!isNotPrime[i / 2]) {
			for (ll j = i * i; j < N; j+= 2 * i) {
				isNotPrime[j / 2] = 1;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	primeSieve();

	ll n;
	cin >> n;
	vector<ll> in(n);
	for (ll& x : in) cin >> x;
	vector<ll> ind;
	for (ll x : in) {
		bool ok = true;
		for (ll y : ind) {
			ok &= !isPrime(x + y);
		}
		if (ok) ind.push_back(x);
	}
	cout << sz(ind) << endl;
}
