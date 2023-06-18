#include <bits/stdc++.h>
using namespace std;

vector<int> operator+(const vector<int> &a, const vector<int> &b) {
	if (a.empty()) return b;
	if (b.empty()) return a;
	assert(size(a) == size(b));
	vector<int> c;
	for (int j: a) c.push_back(b[j]);
	return c;
}

template<typename T>
struct segtree {
	int n;
	vector<T> value;

	segtree(vector<T> leaves): n(leaves.size()), value(2*n) {
		copy(begin(leaves), end(leaves), begin(value)+n);
		for (int i = n-1; i >= 1; i--) {
			value[i] = value[2*i] + value[2*i+1];
		}
	}
	
	void update(int i, T v) {
		i += n;
		value[i] = v;
		for (i /= 2; i; i /= 2) {
			value[i] = value[2*i] + value[2*i+1];
		}
	}
	
	T query(int i, int j) {
		i += n, j += n;
		T resl, resr;
		for (; i < j; i /= 2, j /= 2) {
			if (i & 1) resl = resl + value[i++];
			if (j & 1) resr = value[--j] + resr;
		}
		return resl + resr;
	}
};

vector<int> op(int n, int i) {
	vector<int> v(n);
	iota(begin(v), end(v), 0);
	swap(v[i], v[i+1]);
	return v;
}

int cycle_count(vector<int> p) {
	int n = size(p), res = 0;
	vector<bool> mark(n);
	for (int i = 0; i < n; i++) if (!mark[i]) {
		for (int j = i; !mark[j]; j = p[j]) mark[j] = 1;
		res++;
	}
	return res;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int w, h, q;
	cin >> w >> h >> q;

	vector<vector<int>> leaves(h);
	segtree<vector<int>> S(leaves);
	while (q--) {
		int y, x1, x2;
		cin >> y >> x1 >> x2;
		y--, x1--, x2--;
		int x = min(x1, x2);
		auto v = S.query(y, y+1);
		S.update(y, v.empty() ? op(w, x) : vector<int>(0));

		v = S.query(0, h);
		int res = v.empty() ? 0 : w - cycle_count(v);
		cout << res << '\n';
	}
}
