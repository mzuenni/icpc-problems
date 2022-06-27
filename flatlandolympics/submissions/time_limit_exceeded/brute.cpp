#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ll>;

pt readPT() {
	ll x, y;
	cin >> x >> y;
	return {x, y};
}

ll cross(pt a, pt b) {return imag(conj(a) * b);}
ll cross(pt p, pt a, pt b) {return cross(a - p, b - p);}

ll solve(const vector<pt>& in, pt s, pt e) {
	ll res = 0;
	for (ll i = 0; i < sz(in); i++) {
		for (ll j = 0; j < i; j++) {
			if ((cross(s, e, in[i]) == 0 && cross(s, e, in[j]) == 0) ||
				(cross(in[i], in[j], s) >= 0 && cross(in[i], in[j], e) <= 0) ||
				(cross(in[i], in[j], s) <= 0 && cross(in[i], in[j], e) >= 0)) {
				res++;
			}
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	pt s = readPT();
	pt e = readPT();
	ll n;
	cin >> n;
	vector<pt> left, right;
	for (ll i = 0; i < n; i++) {
		pt c = readPT();
		pt tmp = (c-s)*conj(e-s);
		if (tmp.imag() > 0 || (tmp.imag() == 0 && tmp.real() > 0)) left.push_back(c);
		else right.push_back(c);
	}
	cout << solve(left, s, e) + solve(right, s, e) << endl;
}
