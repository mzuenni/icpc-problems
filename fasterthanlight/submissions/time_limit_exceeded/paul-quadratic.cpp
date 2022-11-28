#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <random>
#include <set>
#include <vector>
using namespace std;
using i64 = long long;

struct point { i64 x, y; };

point operator+(point a,  point b) { return {a.x+b.x, a.y+b.y}; }
point operator-(point a,  point b) { return {a.x-b.x, a.y-b.y}; }
point operator*(i64 t, point b) { return {t*b.x, t*b.y}; }

i64 operator*(point a,  point b) { return a.x*b.x + a.y*b.y; } // dot product
i64 operator%(point a,  point b) { return a.x*b.y - a.y*b.x; } // cross product

bool operator<(point a, point b) { // lexicographical compare
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

int ccw(point a, point b, point c) { // returns 1|0|-1 if c is left|straight|right of ab
	i64 res = (b-a)%(c-a);
	return res ? (res > 0 ? 1 : -1) : 0;
}

struct rectangle {
	i64 x1, y1, x2, y2;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector<rectangle> rectangles(n);
	set<point> corners;
	for (auto &[x1,y1,x2,y2]: rectangles) {
		cin >> x1 >> y1 >> x2 >> y2;
		corners.emplace(x1,y1);
		corners.emplace(x1,y2);
		corners.emplace(x2,y1);
		corners.emplace(x2,y2);
	}

	// shuffle the list of rectangles
	mt19937_64 gen(987);
	shuffle(begin(rectangles), end(rectangles), gen);

	for (const auto &p: corners) {
		auto cmp = [&](const point &a, const point &b) { return ccw(p,a,b) < 0; };
		
		bool found_ab = false; // did we find any rectangle not touching our point?
		bool found_cd = false; // did we find any rectangle not touching our point?
		point a, b, c, d; // [a,b] and [c,d] are the two angle ranges
		bool ok = true;
		for (auto [x1,y1,x2,y2]: rectangles) {
			if (x1 <= p.x && p.x <= x2 && y1 <= p.y && p.y <= y2) continue;

			// Find range of angles covered by the rectangle. Guaranteed to fit strictly within 180 degrees.
			array<point,4> v;
			v[0] = {x1,y1};
			v[1] = {x1,y2};
			v[2] = {x2,y1};
			v[3] = {x2,y2};
			auto e = *min_element(begin(v), end(v), cmp);
			auto f = *max_element(begin(v), end(v), cmp);

			auto intersect = [&](point &g, point &h, bool &found) {
				if (!found) {
					g = e, h = f, found = true;
				} else {
					if (cmp(f,g) || cmp(h,e)) {
						ok = false;
					}
					g = max(g,e,cmp), h = min(h,f,cmp);
				}
			};

			if (p.x > x2 || p.y > y2) {
				e = 2*p - e, f = 2*p - f;
				x1 = 2*p.x - x1, x2 = 2*p.x - x2;
				y1 = 2*p.y - y1, y2 = 2*p.y - y2;
				swap(x1,x2), swap(y1,y2);
			}

			if (p.x < x1) {
				intersect(a, b, found_ab);
			} else if (p.y < y1) {
				intersect(c, d, found_cd);
			} else {
				assert(0);
			}
			if (!ok) break;
		}
		if (ok) {
			// check if the two intervals intersect
			ok = !found_ab || !found_cd ||
				 ccw(p,a,c)*ccw(p,c,b) >= 0 || 
			     ccw(p,a,d)*ccw(p,d,b) >= 0 || 
			     ccw(p,c,a)*ccw(p,a,d) >= 0 || 
			     ccw(p,c,b)*ccw(p,b,d) >= 0;
			if (ok) {
				cout << "possible" << '\n';
				return 0;
			}
		}
	}
	cout << "impossible" << '\n';
}
