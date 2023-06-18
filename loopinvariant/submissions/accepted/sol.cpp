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
	string t = s;
	ll cur = 0;
	ll i = 0;
	do {
		if (s[i] == '(') cur++;
		else cur--;
		i++;
	} while(cur > 0 && i < sz(s));
	rotate(t.begin(), t.begin() + i, t.end());
	if (t == s) {
		cout << "no" << endl;
	} else {
		cout << t << endl;
	}
}
