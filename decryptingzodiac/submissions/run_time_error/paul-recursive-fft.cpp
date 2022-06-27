#include <bits/stdc++.h>
using namespace std;
using C = complex<double>;

vector<C> fft(vector<C> a, int sign) {
	int n = a.size();
	if (n == 1) return a;
	vector<C> b, c;
	for (C x: a) b.push_back(x), swap(b,c);
	b = fft(b,sign), c = fft(c,sign);
	for (int i = 0; i < n/2; i++) {
		C r = polar(1.0, 2*i*sign*M_PI/n);
		a[i]     = b[i] + r * c[i];
		a[n/2+i] = b[i] - r * c[i];
	}
	return a;
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

	p = fft(p,1), q = fft(q,1);

	vector<C> pq(m);
	for (int i = 0; i < m; i++) {
		pq[i] = p[i]*q[i];
	}

	pq = fft(pq,-1);

	vector<int> r(2*K*n);
	for (int i = 0; i < m; i++) {
		r[i%(2*K*n)] += round(real(pq[i])/m);
	}
	reverse(begin(r), end(r));

	int best = 0;
	for (int i = 0; i < 2*K*n; i++) {
		if (i%(2*K) < K) best = max(best, r[i]);
	}

	cout << n-best << endl;
}
