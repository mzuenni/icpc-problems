#include <bits/stdc++.h>
#include "simple_svg_1.0.0.hpp"
using namespace std;
using namespace svg;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using pt = pair<double, double>;
constexpr double inf = 1e18;
//constexpr double scale = 1000;

struct rect {
	double x1, y1, x2, y2;
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	double l = inf;
	double r = -inf;
	double u = -inf;
	double d = inf;
	ll n;
	cin >> n;
	vector<rect> in(n);
	for (ll i = 0; i < n; i++) {
		double x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		in[i] = {x1, y1, x2, y2};
		l = min(l, x1);
		r = max(r, x2);
		u = max(u, y2);
		d = min(d, y1);
	}
	double scale = 1000.0/(r-l);
	double border = 5.0/scale;

	double width = abs(r-l)+2*border;
	double height = abs(u-d)+2*border;
	width *= scale;
	height *= scale;
	Dimensions dimensions(width, height);
	Document doc("image.svg", Layout(dimensions, Layout::BottomLeft));
	for (rect& r : in) {
		r.x1 -= l;
		r.x1 += border;
		r.y1 -= d;
		r.y1 += border;

		r.x1 *= scale;
		r.y1 *= scale;

		r.x2 -= l;
		r.x2 += border;
		r.y2 -= d;
		r.y2 += border;

		r.x2 *= scale;
		r.y2 *= scale;

		Rectangle rr(Point(r.x1, r.y2), r.x2-r.x1, r.y2-r.y1, Fill(Color::Black, 0.5), Stroke(0.1*scale, Color::Black));
		doc << rr;
	}
	doc.save();
}
