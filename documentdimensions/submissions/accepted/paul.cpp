#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		a[i] = size(s) + 1;
	}

	vector<int> s(n+1);
	for (int i = 0; i < n; i++) {
		s[i+1] = s[i]+a[i];
	}

	vector<int> dp(s[n]);
	for (int i = 0; i < n; i++) {
		for (int j = s[i]; j < s[i+1]; j++) dp[j] = i;
	}

	int wmin = *max_element(begin(a), end(a)) - 1;

	int res = 1e8;
	for (int w = wmin; w <= s[n]; w++) {
		int h = 1, i = 0;
		while (true) {
			if (h+w > res) break;
			// find maximal j such that s[j]-s[i]-1 <= w
			int x = s[i]+1 + w;
			if (x >= s[n]) break;
			i = dp[x], h++;
		}
		res = min(res, h+w);
	}
	cout << res << endl;
}
