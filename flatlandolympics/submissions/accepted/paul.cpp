#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 1e5 + 10;

struct bit {
	array<int,N> a = {};

	void add(int i, int x) {
		for (i++; i < N; i += i & -i) a[i] += x;
	}

	int get(int i) {
		int res = 0;
		for (; i ; i -= i & -i) res += a[i];
		return res;
	}
};

i64 count_inversions(vector<int> p, vector<int> q) {
	i64 k = 0, res = 0;
	array<int,N> pos = {};
	for (int x: p) pos[x] = k++;
	bit B;
	for (int x: q) {
		res += B.get(N-1) - B.get(pos[x]);
		B.add(pos[x],1);
	}
	return res;
}

struct point { i64 x, y; };

point operator-(point a, point b) { return {a.x-b.x, a.y-b.y}; }
i64 operator*(point a, point b) { return a.x*b.x + a.y*b.y; }
i64 operator%(point a, point b) { return a.x*b.y - a.y*b.x; }

int main() {
	point s, t;
	cin >> s.x >> s.y >> t.x >> t.y;

	int n; cin >> n;
	vector<point> v(n);
	for (point &p: v) cin >> p.x >> p.y;

	vector<int> up, dn;
	i64 L = 0, R = 0;
	for (int i = 0; i < n; i++) {
		i64 turn = (v[i]-s)%(t-s);
		if (turn) {
			(turn > 0 ? up : dn).push_back(i);
		} else {
			((v[i]-s)*(t-s) < 0 ? L : R)++;
		}
	}
	
	auto solve = [&](vector<int> p) {
		vector<int> q = p;
		auto cmp = [&](int i, int j) {
			i64 turn = (v[i]-s)%(v[j]-s);
			if (turn) return turn > 0;
			return (v[i]-t)%(v[j]-t) < 0;
		};
		for (int dir = 0; dir < 2; dir++) {
			ranges::sort(p, cmp);
			swap(p,q), swap(s,t);
		}
		return count_inversions(p,q);
	};

	i64 res = L*(L-1)/2 + R*(R-1)/2 + solve(up) + solve(dn);
	cout << res << endl;
}
