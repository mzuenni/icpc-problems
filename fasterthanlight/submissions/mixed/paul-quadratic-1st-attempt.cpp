#include <algorithm>
#include <array>
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
		bool found = false; // did we find any rectangle not touching our point?
		point a, b; // start and end of angle range
		bool ok = true;
		for (const auto &[x1,y1,x2,y2]: rectangles) {
			if (x1 <= p.x && p.x <= x2 && y1 <= p.y && p.y <= y2) continue;

			auto cmp = [&](const point &a, const point &b) { return ccw(p,a,b) < 0; };
			array<point,4> v;
			v[0] = {x1,y1};
			v[1] = {x1,y2};
			v[2] = {x2,y1};
			v[3] = {x2,y2};
			auto c = *min_element(begin(v), end(v), cmp);
			auto d = *max_element(begin(v), end(v), cmp);

			if (!found) {
				a = c, b = d;
				found = true;
			} else {
				if (ccw(p,d,a) < 0 || ccw(p,b,c) < 0) {
					ok = false;
					break;
				}
				a = max(a,c,cmp);
				b = min(b,d,cmp);
			}
		}
		if (ok) {
			cout << "possible" << '\n';
			return 0;
		}
	}
	cout << "impossible" << '\n';
}
