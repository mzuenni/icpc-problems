#include <bits/stdc++.h>
#include "visualizer.h"
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;

constexpr ll inf = 0x3FFFFFFF;
constexpr Real eps = 0.00001;

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	Visualizer v(argc, argv);
	
	ll n, m;
	v.testIn >> n >> m;
	vector<Point> in;

	Real l = inf;
	Real r = -inf;
	Real d = inf;
	Real u = -inf;
	for (ll i = 0; i < n; i++) {
		Real x, y;
		v.testIn >> x >> y;
		in.push_back({x, y});
		l = min(l, x);
		r = max(r, x);
		d = min(d, y);
		u = max(u, y);
	}
	l -= 10;
	r += 10;
	d -= 10;
	u += 10;

	v.image.origin = {l, d};
	v.image.dimension = {r-l, u-d};

	for (ll i = 0; i < m; i++) {
		ll a, b;
		v.testIn >> a >> b;
		a--;
		b--;
		Line l(in[a], in[b]);
		l.stroke = Stroke(BLACK, 1, false);
		v.image << l << "\n";
	}

	for (auto [x, y] : in) {
		Line l(x, y, x+eps, y+eps);
		l.stroke = Stroke(BLUE, 5, false);
		l.stroke.value().linecap = Linecap::ROUND;
		v.image << l << "\n";
	}
}
