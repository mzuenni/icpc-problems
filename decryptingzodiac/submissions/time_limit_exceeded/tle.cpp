#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = double;

constexpr ll sigma = 26;
constexpr ll limn = 150000;
constexpr ll lim = 1ll<<19;
static_assert(limn*2 <= lim, "lim too small");

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

vector<vector<cplx>> pa(sigma, vector<cplx>(lim));

vector<ll> solve(const string& b) {
	ll n = sz(b);
	vector<cplx> sum(lim);
	for (ll i = 0; i < sigma; i++) {
		vector<cplx> pb(lim);
		for (ll j = 0; j < n; j++) {
			if (b[n-j-1]- 'a' == i) pb[j].real = 1;
		}
		fft(pb);
		for (ll j = 0; j < lim; j++) {
			sum[j] = sum[j] + (pa[i][j] * pb[j]);
		}
	}
	fft(sum, true);
	vector<ll> res(n);
	for (ll i = 0; i < n; i++) {
		res[i] = round(sum[i + n].real);
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	string a, b;
	cin >> n >> a >> b;
	vector<cplx> sum(lim);
	for (ll i = 0; i < sigma; i++) {
		for (ll j = 0; j < n; j++) {
			if (a[j]- 'a' == i) pa[i][j].real = pa[i][j+n].real = 1;
		}
		fft(pa[i]);
	}
	ll res = n;
	for (ll i = 0; i < sigma; i++) {
		auto tmp = solve(b);
		for (char& c : b) {
			c++;
			if (c > 'z') c -= sigma;
		}
		res = min(res, n-*max_element(all(tmp)));
	}
	cout << res << endl;
}
