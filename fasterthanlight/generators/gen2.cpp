#include "validate.h"
using namespace std;

constexpr Integer lim = 1000000;

using pt = complex<Integer>;

struct rect {
	Integer x1, y1, x2, y2;
};

constexpr Integer query_default = 0;
struct SegTree {
	vector<Integer> tree;

	SegTree(Integer n) : tree(2*n) {}

	Integer combine(Integer a, Integer b) {
		return max(a, b);
	}

	void update(int p, Integer value) {
		for (tree[p += tree.size()/2] = value, p /= 2; p > 0; p /= 2) {
			tree[p] = combine(tree[2*p], tree[2*p+1]);
	}}

	Integer query(int l, int r) {
		Integer resL = query_default;
		Integer resR = query_default;
		for (l += tree.size()/2, r += tree.size()/2; l < r; l /= 2, r /= 2) {
			if (l&1) resL = combine(resL, tree[l++]);
			if (r&1) resR = combine(tree[--r], resR);
		}
		return combine(resL, resR);
	}

	Integer query1(Integer l, Integer val) {
		Integer from = l;
		Integer r = lim;
		while (l + 1 < r) {
			Integer m = (l+r)/2;
			if (query(from, m) <= val) {
				l = m;
			} else {
				r = m;
			}
		}
		return l;
	}

	Integer query2(Integer r, Integer val) {
		Integer l = 0;
		Integer to = r;
		while (l + 1 < r) {
			Integer m = (l+r)/2;
			if (query(m, to) <= val) {
				r = m;
			} else {
				l = m;
			}
		}
		return r;
	}
};

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer limn = arguments["--n"].asInteger(200000);
	Real m = arguments["--m"].asReal(0.842897312798);
	Real c = arguments["--c"].asReal(5.87321);
	bool impossible = arguments["--impossible"].exists();

	bitset<lim> seenY;
	SegTree heightX(lim), heightY(lim);
	vector<Integer> perm(lim - 1);
	for (Integer i = 1; i < lim; i++) perm[i - 1] = i;
	Random::shuffle(perm);

	vector<rect> out;

	for (Integer x : perm) {
		Integer y = m*(x+0.5)+c;
		if (y > 0 && y < lim && !seenY[y]) {
			seenY[y] = true;
			rect cur = {x, y, x+1, y+1};
			Integer dir = Random::integer(0, 4);
			if (dir == 0) {//right
				cur.x2 = heightX.query1(x, y);
				heightY.update(y, cur.x2);
			} else if (dir == 1) {//up
				cur.y2 = heightY.query1(y, x);
				heightX.update(x, cur.y2);
			} else if (dir == 2) {//left
				cur.x1 = heightX.query2(x, y);
				heightY.update(y, cur.x2);
			} else if (dir == 3) {//down
				cur.y1 = heightY.query2(y, x);
				heightX.update(x, cur.y2);
			}

			out.push_back(cur);
		}
	}

	juryOut << "all found: " << out.size() << endl;
	Random::shuffle(out);
	while (out.size() > limn) out.pop_back();
	while (impossible) {
		rect& r = Random::select(out);
		if (r.x1 + 2 < r.x2) r.x2-=2, impossible=false;
		if (r.y1 + 2 < r.y2) r.y2-=2, impossible=false;
	}
	testOut << out.size() << endl;
	for (auto r : out) {
		testOut << r.x1 << " ";
		testOut << r.y1 << " ";
		testOut << r.x2 << " ";
		testOut << r.y2 << endl;
	}
}
