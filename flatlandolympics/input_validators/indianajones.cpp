//checks that no points are equal and that no point is on the track
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ll>;

constexpr int AC = 42;
constexpr int WA = 43;

pt readPT() {
	ll x, y;
	cin >> x >> y;
	return {x, y};
}

ll cross(pt a, pt b) {return imag(conj(a) * b);}

bool pointOnLineSegment(pt a, pt b, pt p) {
	if (cross(b - a, p - a) != 0) return false;
	ll dist = norm(a - b);
	return norm(a - p) <= dist && norm(b - p) <= dist;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	pt s = readPT();
	pt e = readPT();
	if (s == e) return WA;
	ll n;
	cin >> n;
	vector<pt> in(n);
	for (ll i = 0; i < n; i++) {
		in[i] = readPT();
		if (pointOnLineSegment(s, e, in[i])) return WA;
	}
	sort(all(in), [](const pt& a, const pt& b){
		return (imag(a) == imag(b)) ? real(a) < real(b) 
									: imag(a) < imag(b);
	});
	for (ll i = 0; i + 1 < n; i++) {
		if (in[i] == in[i + 1]) return WA;
	}
	return AC;
}
