#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using lll = __int128;
using ld = long double;
using pt = complex<ll>;
template<typename T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
				  tree_order_statistics_node_update>;


pt readPT() {
	ll x, y;
	cin >> x >> y;
	return {x, y};
}

struct point {
	lll x, y;
	ll i;
};

ll inversions(const vector<point>& in) {
	Tree<ll> t; //ordered statistics tree
	ll res = 0;
	for (ll i = 0; i < sz(in); i++) {
		res += i - t.order_of_key(in[i].i);
		t.insert(in[i].i);
	}
	return res;
}

lll sq(lll x) {
	return x*x;
}

ll solve(const vector<pt>& in, ll r) {
	vector<point> tmp;
	for (ll i = 0; i < sz(in); i++) {
		tmp.push_back({in[i].real(), in[i].imag(), -1});
	}
	sort(all(tmp), [](const point& a, const point& b){
		if (a.x*b.y == b.x*a.y) {
			return sq(a.x)+sq(a.y) > sq(b.x)+sq(b.y);
		} else {
			return a.x*b.y < b.x*a.y;
		}
	});
	for (ll i = 0; i < sz(tmp); i++) {
		tmp[i].i = i;
		tmp[i].x -= r;
	}
	sort(all(tmp), [](const point& a, const point& b){
		if (a.x*b.y == b.x*a.y) {
			return sq(a.x)+sq(a.y) < sq(b.x)+sq(b.y);
		} else {
			return a.x*b.y < b.x*a.y;
		}
	});
	return inversions(tmp);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	pt s = readPT();
	pt e = readPT();
	pt dir = e-s;
	pt rot = conj(dir);
	ll n;
	cin >> n;
	vector<pt> upper, lower;
	for (ll i = 0; i < n; i++) {
		pt c = readPT();
		c -= s;
		c *= rot;
		if (c.imag() > 0 || (c.imag() == 0 && c.real() > 0)) upper.push_back(c);
		else lower.push_back(pt(c.real(), -c.imag()));
	}
	e -= s;
	s -= s;
	s *= rot;
	e *= rot;
	cout << solve(upper, real(e)) + solve(lower, real(e)) << endl;
}
