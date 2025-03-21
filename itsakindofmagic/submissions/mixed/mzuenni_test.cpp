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
// (bruteforces to check as few requirements as necessary)
constexpr ll check(ll c, ll lu, ll ru) {
	ll ccc = c * c * c;
	ll cc  = c * c;

	ll cu = ccc / lu / ru;
	if(lu * cu * ru != ccc) return false;

	ll cd = cc / cu;
	if(cu * c * cd != ccc) return false;

	ll rd = cc / lu;

	ll rc = (ccc / ru) / rd;
	if(rc == ru) return false;
	if(ru * rc * rd != ccc) return false;

	ll lc = cc / rc;
	if(lc * c * rc != ccc) return false;

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
		cout << res[r] << "\n";
	}
}
