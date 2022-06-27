#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

bool check(const string& s) {
	vector<pair<char, ll>> enc;
	char last = '#';
	for (char c : s) {
		if (c != last) enc.push_back({c, 0});
		enc.back().second++;
		last = c;
	}
	if (sz(enc) > 4) return false;
	set<char> seen;
	for (auto [c, n] : enc) {
		if (seen.count(c) > 0) return false;
		seen.insert(c);
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> s;
	ll n = sz(s);
	ll res = n;
	if (n > 60) res = -1;
	for (ll i = 0; i < (1ll << n); i++) {
		string tmp;
		for (ll j = 0; j < n; j++) {
			if (((i >> j) & 1) != 0) {
				tmp += s[j];
			}
		}
		if (check(tmp)) res = min(res, n - sz(tmp));
	}
	cout << res << endl;
}
