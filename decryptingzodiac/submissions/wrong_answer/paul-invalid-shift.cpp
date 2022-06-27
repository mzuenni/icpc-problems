#include <bits/stdc++.h>
using namespace std;
using C = complex<double>;

// Based on https://cp-algorithms.com/algebra/fft.html
void fft(vector<C> &a, int sign) {
	int n = a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n/2;
		for (; j & bit; bit /= 2) j ^= bit;
		j ^= bit;

		if (i < j) swap(a[i], a[j]);
	}

	for (int len = 2; len <= n; len *= 2) {
		C wlen = polar(1.0, 2*sign*M_PI / len);
		for (int i = 0; i < n; i += len) {
			C w(1);
			for (int j = 0; j < len/2; j++) {
				C u = a[i+j], v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w *= wlen;
			}
		}
	}

	if (sign < 0) for (C &x: a) x /= n;
}

const int K = 26;
int decode(char c) { return c-'a'; }

int main() {
	int n; cin >> n;
	string a, b;
	cin >> a >> b;

	int m = 1;
	while (m < 4*K*n) m *= 2;

	vector<C> p(m), q(m);
	for (int i = 0; i < n; i++) {
		p[2*i*K + decode(a[i])] = 1;
		q[2*i*K + decode(b[i])] = 1;
		q[(2*i+1)*K + decode(b[i])] = 1;
	}
	reverse(begin(q), begin(q)+2*K*n);

	fft(p,1), fft(q,1);

	vector<C> pq(m);
	for (int i = 0; i < m; i++) {
		pq[i] = p[i]*q[i];
	}

	fft(pq,-1);

	vector<int> r(2*K*n);
	for (int i = 0; i < m; i++) {
		r[i%(2*K*n)] += round(real(pq[i]));
	}

	cout << n - *max_element(begin(r), end(r)) << endl;
}
