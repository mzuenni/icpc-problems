#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
using ll = long long;
using vll = vector<ll>;

#define sz(a) ((ll)(a).size())

constexpr ll p = 1'000'000'007LL;

ll mpow(ll x, ll e) {
	if (e == 0) return 1;
	ll a = mpow(x,e/2);
	(a *= a) %= p;
	if (e%2==1) (a *= x) %= p;
	return a;
}

vll fib = {{0,1}};
vll invFib;

vll solve(ll n) {
	srand(42);
	unordered_map<ll,ll> seen;
	const auto walk = [&](vll& res, ll a) {
		while (a != 1) {
			const ll i = seen.at(a);
			res.emplace_back(i);
			(a *= invFib[i]) %= p;
		}
	};
	ll a = 1, b = 1, l = 0;
	while (true) {
		const ll i = 2 + rand()%98;
		l += i + 1;
		if (l >= 100) {
			a = 1, b = 1, l = 0;
			continue;
		}
		(a *= fib[i]) %= p;
		(b *= invFib[i]) %= p;
		seen[a] = i;
		if (seen.count((b*n)%p)) {
			vll res;
			walk(res, a);
			walk(res, (b*n)%p);
			cerr << seen.size() << endl;
			return res;
		}
	}
}

int main() {
	while (fib.size() <= 100) fib.emplace_back((fib.back() + fib[sz(fib)-2]) % p);
	invFib = fib;
	for (ll& x : invFib) x = mpow(x, p-2);

	ll n; cin >> n;
	if (n < 2) {
		cout << (n==0 ? ".##\n##." : ".\n.");
		return 0;
	}
	auto r = solve(n);
	for (ll c = 0; c < 2; c++) {
		for (ll i = 0; i < r.size(); i++) {
			if (i > 0) cout << '#';
			for (ll j = 1; j < r[i]; j++)
				cout << '.';
		}
		cout << '\n';
	}

	return 0;
}
