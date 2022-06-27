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
	while (m < 2*n) m *= 2;

	vector<vector<C>> p(K, vector<C>(m));
	vector<vector<C>> q(K, vector<C>(m));
	for (int i = 0; i < n; i++) {
		p[decode(a[i])][n-i-1] = 1;
		q[decode(b[i])][i] = 1;
	}
	
	for (int c = 0; c < K; c++) {
		fft(p[c], 1);
		fft(q[c], 1);
	}

	vector<vector<int>> r(K, vector<int>(n));
	for (int c = 0; c < K; c++) {
		for (int d = 0; d < K; d++) {
			vector<C> pq(m);
			for (int i = 0; i < m; i++) {
				pq[i] = p[c][i] * q[d][i];
			}
			fft(pq, -1);
			
			int k = (d-c+K) % K;
			for (int i = 0; i < m; i++) {
				r[k][i%n] += round(real(pq[i]));
			}
		}
	}
	
	int res = 0;
	for (auto v: r) for (int x: v) res = max(res,x);
	res = n-res;

	cout << res << endl;

}
