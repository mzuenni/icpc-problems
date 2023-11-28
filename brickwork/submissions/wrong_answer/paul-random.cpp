#include <bits/stdc++.h>
using namespace std;

vector<int> find_random_partition(const vector<int> &a, int n, double timeout) {
	clock_t start = clock();
	vector<int> v(n+1);
	while (double(clock()-start)/CLOCKS_PER_SEC < timeout) {
		int r = n, k = 0, m = size(a);
		while (r > 0) {
			while (m > 0 && a[m-1] > r) m--;
			if (m == 0) break;
			int i = a[m-1] == r ? m-1 : rand() % m;
			v[k] = a[i];
			r -= v[k++];
		}
		if (r == 0) {
			v.resize(k);
			return v;
		}
	}
	return {};
}

void fail() {
	cout << "impossible" << '\n';
	exit(0);
}

void print_vector(const vector<int> &v) {
	int n = size(v);
	cout << n << '\n';
	for (int i = 0; i < n; i++) {
		cout << v[i] << " \n"[i+1==n];
	}
}

int main() {
	srand(987);

	int m, n;
	cin >> m >> n;

	vector<int> a(m);
	for (int &x: a) cin >> x;
	sort(begin(a), end(a));
	a.erase(unique(begin(a), end(a)), end(a));
	while (!a.empty() && a.back() > n) a.pop_back();
	m = size(a);

	auto v = find_random_partition(a, n, 1.0);
	if (v.empty()) fail();
	sort(begin(v), end(v));

	vector<int> w;
	for (int j = 0; j < 5; j++) {
		w = find_random_partition(a, n, 0.1);
		if (w.empty()) continue;
		sort(begin(w), end(w));
		if (w != v) break;
	}
	if (w.empty()) w = v;

	clock_t start = clock();
	while (double(clock()-start)/CLOCKS_PER_SEC < 1.2) {
		random_shuffle(begin(v), end(v));
		random_shuffle(begin(w), end(w));
		int a = v[0], b = w[0], i = 1, j = 1;
		while (a < n || b < n) {
			if (a == b) break;
			if (a < b) {
				a += v[i++];
			} else {
				b += w[j++];
			}
			if (a == n) {
				cout << "possible" << '\n';
				print_vector(v);
				print_vector(w);
				return 0;
			}
		}
	}

	fail();
}
