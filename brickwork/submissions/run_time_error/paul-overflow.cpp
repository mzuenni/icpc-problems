#include <bits/stdc++.h>
using namespace std;

void print(vector<int> p) {
	cout << size(p) << '\n';
	bool first = true;
	for (int x: p) {
		if (first) first = false;
		else cout << ' ';
		cout << x;
	}
	cout << '\n';
}

void success(vector<int> p, vector<int> q) {
	cout << "possible" << '\n';
	print(p), print(q);
	exit(0);
}

void fail() {
	cout << "impossible" << '\n';
	exit(0);
}

const int W = 300'005;

int main() {
	int n, w;
	cin >> n >> w;

	// Read brick widths, sort and deduplicate.
	vector<int> a(n);
	for (int &x: a) cin >> x;
	sort(begin(a), end(a));
	a.erase(unique(begin(a), end(a)), end(a));
	n = size(a);

	// If a single brick covers the full width, just use that brick twice.
	if (find(begin(a), end(a), w) != end(a)) success({w}, {w});

	// Compute all the numbers that are a multiple of some brick width.
	bitset<W> steps;
	for (int x: a) {
		for (int y = x; y < W; y += x) steps[y] = 1;
	}

	// Compute all the numbers that can be formed from the given bricks.
	bitset<W> dp;
	dp[0] = 1;
	for (int x = 1; x < W; x++) {
		if (steps[x]) dp |= dp << x;
	}

	// Compute up to two partitions of the width into sums of bricks.
	vector<vector<int>> res;
	for (int i = 0; i < n; i++) {
		if (a[i] <= w && dp[w-a[i]]) {
			vector<int> p = {a[i]};
			int r = w-a[i];
			for (int x: a) {
				while (x <= r && dp[r-x]) p.push_back(x), r -= x;
			}
			sort(begin(p), end(p));
			res.push_back(p);
		}
		if (ssize(res) == 2) break;
	}

	// If only one partition was found, then it must consist of just a single
	// brick width. As we must use at least two copies of that brick per row,
	// it is impossible to avoid alignments.
	if (ssize(res) < 2) fail();

	// If we found two partitions, then a solution always exists, but we need
	// to consider two cases. First, if the two solutions both consist of just
	// a single type of brick, then the way in which we created the partitions
	// (always using the shortest possible brick) guarantees that there are no
	// alignments. Any such alignment would imply that the two brick lengths
	// have a common multiple strictly less than the width of the wall and our
	// method would therefore have switched from the longer brick to the
	// shorter one.
	if (res[0][0] == res[0].back() && res[1][0] == res[1].back()) {
		success(res[0], res[1]);
	}
	
	// In the second case we found a solution consisting of at least two
	// distinct lengths and we can create two rows based on this solution.
	for (auto p: res) if (p[0] != p.back()) {
		map<int,int> c;
		for (int x: p) c[x]++;

		// We only need to find a way of assembling the two shortest brick
		// types without alignment, as we can then always insert the longer
		// bricks in a suitable way, for instance by placing them all after the
		// first brick of the first row:
		//
		// [-x-][-x-][--y--]         [-x-][----w----][----w----][-x-][--y--]
		// [--y--][-x-][-x-]   ->    [--y--][----w----][----w----][-x-][-x-]
		//
		// Suppose these two shortest brick lengths are x and y, and put z =
		// lcm(x, y). While there are strictly more than z/x copies of x, we
		// can keep replacing z/x copies of x by z/y copies of y.
		int x = begin(c)->first, y = next(begin(c))->first, z = lcm(x, y);
		while (c[x] > z/x) c[x] -= z/x, c[y] += z/y;

		vector<int> q, r;
		if (c[x] < z/x) {
			// If there are now strictly fewer than z/x copies of x remaining,
			// then the sequence with all x before all y does not have any
			// alignment with the sequence of all y before all x. For if there
			// were such an alignment, there would be d with 0 < d <= c[x] such
			// that d*x is a multiple of both x and y, contradicting the
			// definition of z.
			q.assign(c[x], x);
			q.resize(c[x]+c[y], y);
			r.assign(c[y], y);
			r.resize(c[x]+c[y], x);
		} else {
			// If instead c[x] == z/x, then we form two distinct walls, where
			// one of them has exactly c[x] copies of x, and the other consists
			// exclusively of copies of y. A similar argument to the previous
			// case shows that there are no alignments.
			q.assign(c[x]-1, x);
			q.resize(c[x]+c[y]-1, y);
			q.push_back(x);
			r.assign(c[y]+z/y, y);
		}

		// Now we insert the longer bricks in the way discussed above.
		vector<int> s;
		for (auto [w,k]: c) if (w > y) while (k--) s.push_back(w);
		q.insert(begin(q)+1, begin(s), end(s));
		r.insert(begin(r)+1, begin(s), end(s));

		success(q, r);
	}
}
