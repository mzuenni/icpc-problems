#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ll>;
constexpr ll lim = 1000000007;

// Kreuzprodukt, 0, falls kollinear.
ll cross(pt a, pt b) {return imag(conj(a) * b);}
ll cross(pt p, pt a, pt b) {return cross(a - p, b - p);}

bool ptless(const pt& a, const pt& b) {
	return real(a) == real(b) ? imag(a) < imag(b)
							  : real(a) < real(b);
}

deque<pt> convexHull(deque<pt>& p){
	int k = 0;
	deque<pt> h(2 * sz(p));
	for (int i = 0; i < sz(p); i++) {// Untere Hülle.
		while (k >= 2 && cross(h[k-2], h[k-1], p[i]) <= 0) k--;
		h[k++] = p[i];
	}
	for (int i = sz(p)-2, t = k; i >= 0; i--) {// Obere Hülle.
		while (k > t && cross(h[k-2], h[k-1], p[i]) <= 0) k--;
		h[k++] = p[i];
	}
	h.resize(k);
	return h;
}

void lowerHull(deque<pt>& p) {
	sort(p.begin(), p.end(), ptless);
	p.erase(unique(p.begin(), p.end()), p.end());
	p.push_front(pt(real(p.front()) - 1, lim));
	p.push_back(pt(real(p.back()) + 1, lim));
	p = convexHull(p);
	p.pop_front();
	p.pop_back();
	p.pop_back();
}

void upperHull(deque<pt>& p) {
	sort(p.begin(), p.end(), ptless);
	p.erase(unique(p.begin(), p.end()), p.end());
	p.push_front(pt(real(p.front()) - 1, -lim));
	p.push_back(pt(real(p.back()) + 1, -lim));
	p = convexHull(p);
	reverse(all(p));
	p.pop_front();
	p.pop_back();
	p.pop_back();
}

bool solve(deque<pt>& upper, deque<pt>& lower) {
	lowerHull(upper);//yes this is right...
	upperHull(lower);
	ll u = 0;
	ll l = 0;
	while (u < sz(upper) && l < sz(lower)) {
		if (real(upper[u]) == real(lower[l])) {
			if (imag(upper[u]) < imag(lower[l])) return false;
			u++;
			l++;
		} else if (real(upper[u]) < real(lower[l])) {
			if (l > 0 && cross(upper[u], lower[l-1], lower[l]) < 0) return false;
			u++;
		} else {
			if (u > 0 && cross(lower[l], upper[u-1], upper[u]) > 0) return false;
			l++;
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	deque<pt> upper1(n), lower1(n), upper2(n), lower2(n);
	ll l = 0;
	ll r = lim;
	for (ll i = 0; i < n; i++) {
		ll x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		l = max(l, x1);
		r = min(r, x2);
		lower1[i] = pt(x1, y1);
		upper1[i] = pt(x2, y2);
		lower2[i] = pt(x2, y1);
		upper2[i] = pt(x1, y2);
	}
	cout << (solve(upper1, lower1) ||
			 solve(upper2, lower2) ? "possible" : "impossible") << endl;
}
