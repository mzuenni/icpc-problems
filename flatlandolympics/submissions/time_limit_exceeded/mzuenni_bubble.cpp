#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ll>;
template<typename T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
				  tree_order_statistics_node_update>;

ll cross(pt a, pt b) {return imag(conj(a) * b);}

pt readPT() {
	ll x, y;
	cin >> x >> y;
	return {x, y};
}

struct point {
	pt p;
	ll i;
};

ll inversions(vector<point>& in) {
	ll res = 0;
	for (ll i = 0; i < sz(in); i++) {
		for (ll j = 0; j + 1 < sz(in) - i; j++) {
			if (in[j].i > in[j + 1].i) {
				res++;
				swap(in[j].i, in[j + 1].i);
			}
		}
	}
	return res;
}

ll solve(const vector<pt>& in, pt e) {
	vector<point> tmp;
	for (ll i = 0; i < sz(in); i++) {
		tmp.push_back({in[i], -1});
	}
	sort(all(tmp), [](const point& a, const point& b){
		if (cross(a.p, b.p) == 0) {
			return norm(a.p) > norm(b.p);
		} else {
			return cross(a.p, b.p) < 0;
		}
	});
	for (ll i = 0; i < sz(tmp); i++) {
		tmp[i].i = i;
		tmp[i].p -= e;
	}
	sort(all(tmp), [](const point& a, const point& b){
		if (cross(a.p, b.p) == 0) {
			return norm(a.p) < norm(b.p);
		} else {
			return cross(a.p, b.p) < 0;
		}
	});
	return inversions(tmp);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	pt s = readPT();
	pt e = readPT();
	e -= s;
	pt orth = e * pt(0, 1);
	ll n;
	cin >> n;
	vector<pt> upper, lower;
	for (ll i = 0; i < n; i++) {
		pt c = readPT();
		c -= s;
		if (cross(e, c) > 0 || (cross(e, c) == 0 && cross(orth, c) < 0)) upper.push_back(c);
		else lower.push_back(-c+e);
	}
	cout << solve(upper, e) + solve(lower, e) << endl;
}
