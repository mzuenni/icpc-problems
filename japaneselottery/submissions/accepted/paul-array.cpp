#include <bits/stdc++.h>
using namespace std;

const int W = 20;
using perm = array<int,W>;

perm operator+(const perm &a, const perm &b) {
	perm c;
	for (int i = 0; i < W; i++) {
		c[i] = b[a[i]];
	}
	return c;
}

template<typename T>
struct segtree {
	int n;
	T unit;
	vector<T> value;

	segtree(T unit, vector<T> leaves): n(leaves.size()), unit(unit), value(2*n) {
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
		T resl = unit, resr = unit;
		for (; i < j; i /= 2, j /= 2) {
			if (i & 1) resl = resl + value[i++];
			if (j & 1) resr = value[--j] + resr;
		}
		return resl + resr;
	}
};

int cycle_count(perm p) {
	int res = 0;
	vector<bool> mark(W);
	for (int i = 0; i < W; i++) if (!mark[i]) {
		for (int j = i; !mark[j]; j = p[j]) mark[j] = 1;
		res++;
	}
	return res;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int w, h, q;
	cin >> w >> h >> q;

	perm id;
	iota(begin(id), end(id), 0);

	vector<perm> sw(w-1, id);
	for (int i = 0; i < w-1; i++) {
		swap(sw[i][i], sw[i][i+1]);
	}

	vector<perm> leaves(h, id);
	segtree<perm> S(id, leaves);
	while (q--) {
		int y, x1, x2;
		cin >> y >> x1 >> x2;
		y--, x1--, x2--;
		int x = min(x1, x2);
		auto v = S.query(y, y+1);
		S.update(y, v == id ? sw[x] : id);

		v = S.query(0, h);
		int res = v == id ? 0 : W - cycle_count(v);
		cout << res << '\n';
	}
}
