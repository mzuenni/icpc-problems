#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> s;
	ll n = s.size();
	string t = s;
	s += s;

	ll cur = 0;
	ll i = 0;
	do {
		if (s[i] == '(') cur++;
		else cur--;
		i++;
		if (cur == 0) {
			bool match = true;
			for (ll j = 0; j < n && match; j++) match = s[j] == s[i+j];
			if (!match) break;
		}
	} while(i < n);
	if (i < n) {
		rotate(t.begin(), t.begin() + i, t.end());
		cout << t << endl;
	} else {
		cout << "no" << endl;
	}
}
