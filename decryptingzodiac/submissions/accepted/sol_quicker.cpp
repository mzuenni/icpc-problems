#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = double;

constexpr ll sigma = 26;
constexpr ll limn = 150000;
constexpr ll lim = 1ll<<24;
static_assert(limn*sigma*4 <= lim, "lim too small");


struct cplx {
	ld real;
	ld imag;

	constexpr cplx() : real(0), imag(0) {};
	constexpr cplx(ld real, ld imag) : real(real), imag(imag) {};

	constexpr cplx conj() const {
		return cplx(real, -imag);
	}
};

constexpr cplx operator+(const cplx& a, const cplx& b) {
	return cplx(a.real + b.real, a.imag + b.imag);
}

constexpr cplx operator-(const cplx& a, const cplx& b) {
	return cplx(a.real - b.real, a.imag - b.imag);
}

constexpr cplx operator*(const cplx& a, const cplx& b) {
	return cplx(a.real * b.real - a.imag * b.imag,
			a.real * b.imag + a.imag * b.real);
}

constexpr cplx operator/(const cplx& a, ld b) {
	return cplx(a.real / b, a.imag / b);
}

void operator/=(cplx& a, ld b) {
	a.real /= b;
	a.imag /= b;
}

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
			cplx w(1, 0);
			for (int k = 0; k < s; k++) {
				cplx u = a[j + k], t = a[j + s + k] * w;
				a[j + k] = u + t;
				a[j + s + k] = u - t;
				if (inverse) a[j + k] /= 2, a[j + s + k] /= 2;
				w = w*ws;
}}}}

vector<ll> solve(const string& a, const string& b) {
	ll n = sz(a);
	vector<cplx> pa(lim), pb(lim);
	for (ll i = 0; i < n; i++) {
		pa[2*sigma*(i) + a[i]-'a'].real = 1;
		pa[2*sigma*(i+n) + a[i]-'a'].real = 1;

		pa[2*sigma*(i+1) - 1 -(b[n-i-1]-'a')].imag = 1;
		pa[2*sigma*(i+1) - 1 -(b[n-i-1]-'a') - sigma].imag = 1;
	}
	fft(pa);
	for (ll i = 0; i < lim; i++) {
		ll j = (lim - i) % lim;
		cplx x = (pa[i] + pa[j].conj()) / 2;
		cplx y = cplx(0, 1) * (pa[i] - pa[j].conj()) / -2;
		pb[i] = x * y;
	}
	fft(pb, true);
	vector<ll> res;
	for (ll dx = n-1; dx >= 0; dx--) {
		for (ll dc = sigma - 1; dc < 2*sigma - 1; dc++) {
			res.push_back(round(pb[dx*2*sigma+dc + 2*sigma*n].real));
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	string a, b;
	cin >> n >> a >> b;
	auto res = solve(a, b);
	cout << n-*max_element(all(res)) << endl;
}
