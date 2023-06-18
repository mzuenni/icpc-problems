#include <iostream>
#include <vector>

using namespace std;

constexpr int oo = 0x3f3f3f3f;

struct Tree {
	typedef int T;
	static constexpr T unit = oo;
	T f(const T& a, const T& b) { return min(a, b); } // any associative function
	vector<T> s; int n;
	Tree(int n = 0, T init = unit) : s(2*n, init), n(n) {}
	void update(int i, const T& val) {
		for(s[i += n] = val; i /= 2;)
			s[i] = f(s[i*2], s[i*2+1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for(b += n, e += n; b < e; b /= 2, e /= 2) {
			if(b % 2 != 0) ra = f(ra, s[b++]);
			if(e % 2 != 0) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main() {
	cin.tie(nullptr), ios_base::sync_with_stdio(false);

	int n;
	cin >> n;

	Tree tree(2.1e6);
	for (int i = 0; i < tree.n; i++)
		tree.update(i, i);

	vector<int> pos(n);
	for (int& x : pos) cin >> x, tree.update(x, oo);

	int q;
	cin >> q;
	while (q-- > 0) {
		int id;
		cin >> id;
		id--;

		tree.update(pos[id], pos[id]);
		pos[id] = tree.query(pos[id]+1, tree.n);
		tree.update(pos[id], 1e6);
		cout << pos[id] << '\n';
	}

	return 0;
}
