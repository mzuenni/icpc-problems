#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll maxN = 1000;
constexpr ll maxC = 1000;
constexpr ll precision = 3;
//constexpr ll seed = 123456789;
ll seed = time(nullptr);
mt19937 rng(seed);


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n = uniform_int_distribution<ll>(1, maxN)(rng);
	ld p = uniform_real_distribution<ld>(0, 1)(rng);

	cout << fixed << setprecision(precision);
	cout << n << " " << p << endl;
	for (ll i = 0; i < n; i++) {
		ll c = uniform_int_distribution<ll>(1, maxC)(rng);
		ld p = uniform_real_distribution<ld>(0, 1)(rng);
		cout << c << " " << p << endl;
	}
}
