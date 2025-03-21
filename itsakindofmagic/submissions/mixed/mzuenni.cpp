// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED

#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

// lu cu ru
// lc  c rc
// ld cd rd
//
// lu teilt c*c
// ru teilt c*c
constexpr ll check(ll c, ll lu, ll ru) {
	ll ccc = c * c * c;
	ll cc  = c * c;

	if((ccc / lu) % ru != 0) return false;
	ll cu = ccc / lu / ru;
	// check row 1
	if(cc % cu != 0) return false;

	ll ld = cc / ru; // => diag 2 correct by definition
	ll cd = cc / cu; // => col 2 correct by definition
	ll rd = cc / lu; // => diag 1 correct by definition
	// check row 3
	if((ccc / ld) % cd != 0) return false;
	if((ccc / ld) / cd != rd) return false;

	if((ccc / ru) % rd != 0) return false;
	ll rc = (ccc / ru) / rd;
	// check col 3
	if(cc % rc != 0) return false;
	ll lc = cc / rc;
	// => row 2 correct by definition

	// check col 1
	if((ccc / lu) % lc != 0) return false;
	if((ccc / lu) / lc != ld) return false;

	// check unique
	array<ll, 9> tmp = {lu, cu, ru, lc, c, rc, ld, cd, rd};
	sort(all(tmp));
	for(ll i = 1; i < 9; i++) {
		if(tmp[i] == tmp[i - 1]) return false;
	}
	return true;
}

ll brute(ll c) {
	vector<ll> divs;
	for(ll lu = 1; lu < c; lu++) {
		if((c * c) % lu == 0) {
			divs.push_back(lu);
		}
	}

	ll res = 0;
	for(ll i = 0; i < sz(divs); i++) {
		ll lu = divs[i];
		ll rd = (c * c) / lu;
		for(ll j = i + 1; j < sz(divs) && divs[j] < rd; j++) {
			ll ru = divs[j];
			res += check(c, lu, ru);
		}
	}
	return 8 * res;
}

constexpr ll lim = 1'000'007;
ll primes[7]     = {2, 3, 5, 7, 11, 13, 17};
vector<ll> powers[7];
ll divisor[lim];
ll res[lim];

void calcRes() {
	for(ll i = 0; i < 7; i++) {
		powers[i] = {1};
		while(powers[i].back() < lim) powers[i].push_back(powers[i].back() * primes[i]);
	}
	vector<ll> count;
	count.reserve(8);
	for(ll i = 2; i < lim; i++) {
		if(divisor[i] == 0) {
			divisor[i] = i;
			for(ll j = i * i; j < lim; j += i) {
				divisor[j] = i;
			}
		}
		count.clear();
		ll j = i;
		while(j > 1) {
			ll d = divisor[j];
			ll c = 0;
			do {
				c++;
				j /= d;
			} while(j % d == 0);
			count.push_back(c);
		}
		sort(all(count), greater<ll>{});
		ll k = 1;
		for(ll j = 0; j < sz(count); j++) k *= powers[j][count[j]];
		res[i] = res[k];
		if(k == i) res[i] = brute(k);
	}
	for(ll i = 1; i < lim; i++) res[i] += res[i - 1];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	calcRes();

	ll n;
	cin >> n;
	for(ll i = 0; i < n; i++) {
		ll x;
		cin >> x;
		ll r = std::cbrtl(x);
		while((r + 1) * (r + 1) * (r + 1) <= x) r++;
		while(r * r * r > x) r--;
		cout << res[r] << "\n";
	}
}
