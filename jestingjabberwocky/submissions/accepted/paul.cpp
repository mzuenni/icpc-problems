#include <bits/stdc++.h>
using namespace std;

int main() {
	string s; cin >> s;

	string p = s;
	sort(begin(p), end(p));
	p.erase(unique(begin(p), end(p)), end(p));
	int k = size(p);

	int res = 1e9;
	do {
		vector<int> dp(k);
		for (char c: s) {
			vector<int> ndp(k, 1e9);
			for (int i = 0; i < k; i++) {
				ndp[i] = dp[i] + (p[i] != c);
				if (i > 0) ndp[i] = min(ndp[i], ndp[i-1]);
			}
			dp = ndp;
		}
		res = min(res, dp.back());
	} while (next_permutation(begin(p), end(p)));
	cout << res << '\n';
}
