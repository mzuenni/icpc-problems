#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll sigma = 8;
constexpr ll limn = 16;
constexpr ll lim = 1ll<<9;
static_assert(limn*sigma*4 <= lim, "lim too small");

using cplx = complex<ld>;
constexpr ld PI = acos(-1);

void fft(vector<cplx>& a, bool inverse = 0) {
	int n = sz(a);
	for (int i = 0, j = 1; j < n - 1; ++j) {
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
	for (int s = 1; s < n; s *= 2) {
		ld angle = PI / s * (inverse ? -1 : 1);
		cplx ws(cos(angle), sin(angle));
		for (int j = 0; j < n; j+= 2 * s) {
			cplx w = 1;
			for (int k = 0; k < s; k++) {
				cplx u = a[j + k], t = a[j + s + k] * w;
				a[j + k] = u + t;
				a[j + s + k] = u - t;
				if (inverse) a[j + k] /= 2, a[j + s + k] /= 2;
				w *= ws;
}}}}

vector<ll> solve(const string& a, const string& b) {
	ll n = sz(a);
	vector<cplx> pa(lim), pb(lim);
	for (ll i = 0; i < n; i++) {
		pa[2*sigma*(i) + a[i]-'a'] = 1;
		pa[2*sigma*(i+n) + a[i]-'a'] = 1;

		pb[2*sigma*(i+1) - 1 -(b[n-i-1]-'a')] = 1;
		pb[2*sigma*(i+1) - 1 -(b[n-i-1]-'a') - sigma] = 1;
	}
	fft(pa);
	fft(pb);
	for (ll i = 0; i < lim; i++) pa[i] *= pb[i];
	fft(pa, true);
	vector<ll> res;
	for (ll dx = n-1; dx >= 0; dx--) {
		for (ll dc = sigma - 1; dc < 2*sigma - 1; dc++) {
			res.push_back(round(real(pa[dx*2*sigma+dc + 2*sigma*n])));
		}
	}
	return res;
}

vector<ll> wa1(const string& a, const string& b) {
	ll n = sz(a);
	vector<cplx> pa(lim), pb(lim);
	for (ll i = 0; i < n; i++) {
		pa[sigma*(i) + a[i]-'a'] = 1;
		pa[sigma*(i+n) + a[i]-'a'] = 1;

		pb[sigma*(i+1) - 1 -(b[n-i-1]-'a')] = 1;
	}
	fft(pa);
	fft(pb);
	for (ll i = 0; i < lim; i++) pa[i] *= pb[i];
	fft(pa, true);
	vector<ll> res;
	for (ll dx = n-1; dx >= 0; dx--) {
		for (ll dc = 0; dc < sigma; dc++) {
			res.push_back(round(real(pa[dx*2*sigma+dc + 2*sigma*n])));
		}
	}
	return res;
}

vector<ll> wa2(const string& a, const string& b) {
	ll n = sz(a);
	vector<cplx> pa(lim), pb(lim);
	for (ll i = 0; i < n; i++) {
		pa[2*sigma*(i) + a[i]-'a'] = 1;
		pa[2*sigma*(i+n) + a[i]-'a'] = 1;

		pb[2*sigma*(i+1) - 1 -(b[n-i-1]-'a')] = 1;
		pb[2*sigma*(i+1) - 1 -(b[n-i-1]-'a') - sigma] = 1;
	}
	fft(pa);
	fft(pb);
	for (ll i = 0; i < lim; i++) pa[i] *= pb[i];
	fft(pa, true);
	vector<ll> res;
	for (ll dx = n-1; dx >= 0; dx--) {
		for (ll dc = 0; dc < sigma; dc++) {
			res.push_back(round(real(pa[dx*2*sigma+dc + 2*sigma*n])));
		}
	}
	return res;
}

vector<ll> wa3(const string& a, const string& b) {
	ll n = sz(a);
	vector<cplx> pa(lim), pb(lim);
	for (ll i = 0; i < n; i++) {
		pa[2*sigma*(i) + a[i]-'a'] = 1;
		pa[2*sigma*(i+n) + a[i]-'a'] = 1;

		pb[2*sigma*(i+1) - 1 -(b[n-i-1]-'a')] = 1;
		pb[2*sigma*(i+1) - 1 -(b[n-i-1]-'a') - sigma] = 1;
	}
	fft(pa);
	fft(pb);
	for (ll i = 0; i < lim; i++) pa[i] *= pb[i];
	fft(pa, true);
	vector<ll> res;
	for (ll dx = n-1; dx >= 0; dx--) {
		for (ll dc = 0; dc < 2*sigma; dc++) {
			res.push_back(round(real(pa[dx*2*sigma+dc + 2*sigma*n])));
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	mt19937 rng(123456789);
	while (true) {
		for (ll l = 1; l <= limn; l++) {
			cout << l << endl;
			string a(l, '*'), b(l, '*');
			for (ll i = 0; i < 1000; i++) {
				for (char& c : a) c = uniform_int_distribution<char>(0, sigma - 1)(rng) + 'a';
				for (char& c : b) c = uniform_int_distribution<char>(0, sigma - 1)(rng) + 'a';
				auto r1 = solve(a, b);
				auto r2 = wa1(a, b);
				auto r3 = wa2(a, b);
				auto r4 = wa3(a, b);
				if (*max_element(all(r1)) > *max_element(all(r2)) && 
					*max_element(all(r1)) != *max_element(all(r3)) &&
					*max_element(all(r1)) != *max_element(all(r4))) {
					cout << l << endl;
					cout << a << endl;
					cout << b << endl;
					return 0;
				}
			}
		}
	}
}
