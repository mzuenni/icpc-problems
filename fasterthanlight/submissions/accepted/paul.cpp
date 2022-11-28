#include <array>
#include <iostream>
#include <vector>
#include <algorithm>
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

ostream &operator<<(ostream &out, point a) { // for debugging
	return out << "(" << a.x << "," << a.y << ")";
}

i64 abs2(point a) { return a*a; }
point perp(point a) { return {-a.y,a.x}; } // rotate 90 degrees counterclockwise

int ccw(point a, point b, point c) { // returns 1|0|-1 if c is left|straight|right of ab
	i64 res = (b-a)%(c-a);
	return res ? (res > 0 ? 1 : -1) : 0;
}

bool on_segment(point p, point a, point b) {
	return (a-p)*(b-p) <= 0 && ccw(a,b,p) == 0;
}

void convex_hull(vector<point> &p) {
	partial_sort(begin(p), begin(p)+1, end(p));
	sort(begin(p)+1, end(p), [&](point a, point b) {
		if (int c = ccw(p[0],a,b)) return c == 1;
		return abs2(a-p[0]) < abs2(b-p[0]);
	});
	int n = size(p), k = 2;
	for (int i = 2; i < n; i++) {
		p[k++] = p[i];
		while (k >= 3 && ccw(p[k-3],p[k-2],p[k-1]) <= 0) p[k-2] = p[k-1], k--;
	}
	p.resize(k);
}

bool can_divide(vector<point> a, vector<point> b) {
	convex_hull(a), convex_hull(b);
	for (int dir = 0; dir < 2; dir++) {
		int m = size(a), n = size(b);
		auto cross = [&](int i, int j) {
			return (a[(i+1)%m]-a[i]) % b[j];
		};
		int j = 0;
		for (int k = 1; k < n; k++) {
			if (cross(0,k) > cross(0,j)) j = k;
		}
		for (int i = 0; i < m; i++) {
			while (cross(i,(j+1)%n) > cross(i,j)) j = (j+1)%n;
			if (cross(i,j) <= a[(i+1)%m] % a[i]) return true;
		}
		swap(a,b);
	}
	return false;
}

int main() {
	int n; cin >> n;
	vector<vector<point>> corners(4, vector<point>(n));
	for (int i = 0; i < n; i++) {
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		corners[0][i] = {x1,y1};
		corners[1][i] = {x1,y2};
		corners[2][i] = {x2,y2};
		corners[3][i] = {x2,y1};
	}

	bool res = can_divide(corners[0], corners[2]) || can_divide(corners[1], corners[3]);
	cout << (res ? "possible" : "impossible") << '\n';
}
