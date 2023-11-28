#include <bits/stdc++.h>
using namespace std;

const int N = 333333;
int dp[N], go[N][2];

int main() {
	srand(123);

	int n, m;
	cin >> n >> m;

	vector<int> a(n);
	for (int &x: a) cin >> x;
	sort(begin(a), end(a));
	a.erase(unique(begin(a), end(a)), end(a));
	n = size(a);

	if (find(begin(a), end(a), m) != end(a)) {
		cout << "possible" << '\n' << 1 << '\n' << m << '\n' << 1 << '\n' << m << '\n';
		return 0;
	}

	dp[0] = 1;
	for (int i = 1; i <= m; i++) {
		for (int x: a) {
			if (x > i) break;
			if (!dp[i-x]) continue;
			go[i][dp[i]++] = x;
			if (dp[i] == 2) break;
		}
	}

	cout << (dp[m] == 2 ? "possible" : "impossible") << '\n';
	if (dp[m] < 2) return 0;

	vector<int> u, v;
	while (true) {
		int j = m, k = m;
		u.clear(), v.clear();
		while (j+k > 0) {
			if (j < k) swap(j, k), swap(u, v);
			int x = go[j][0], y = go[j][1], z;
			bool b = x > 0 && (j-x != k || k == 0);
			bool c = y > 0 && (j-y != k || k == 0);
			if (b && c) z = rand() % 2 ? x : y;
			else if (b) z = x;
			else if (c) z = y;
			else break;
			u.push_back(z), j -= z;
		}
		if (j+k == 0) break;
	}
	cout << size(u) << '\n';
	for (int x: u) cout << x << ' ';
	cout << '\n';
	cout << size(v) << '\n';
	for (int x: v) cout << x << ' ';
	cout << '\n';
}
