#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

using ll = long long;
using vll = vector<ll>;

#define sz(a) ((ll)(a).size())

bool valid(const string& s) {
	ll o = 0;
	for (char c : s) {
		o += c == '(' ? 1 : -1;
		if (o < 0) return false;
	}
	return o == 0;
}

int main() {
	string s;
	cin >> s;
	
	string rev(s.crbegin(), s.crend());
	for (char& c : rev) c = '(' + ')' - c;
	if (rev == s) {
		cout << "no\n";
		return 0;
	}
	ll p = 0;
	for (ll c = 0; p < sz(s); p++) {
		c += s[p] == '(' ? 1 : -1;
		if (c == 0) break;
	}
	rotate(s.begin(), s.begin() + p + 1, s.end());
	cout << s << endl;

	return 0;
}
