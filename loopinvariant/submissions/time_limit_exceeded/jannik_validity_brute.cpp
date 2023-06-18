#include <iostream>
#include <algorithm>
#include <random>
#include <string_view>

using namespace std;

using ll = long long;
using vll = vector<ll>;

#define sz(a) ((ll)(a).size())

bool valid(const string_view& s) {
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
	ll n = s.size();
	
	for (ll l = 1; l < n; l++)
		if (valid(string_view(s).substr(0, l))) {
			const auto res = s.substr(l) + s.substr(0,l);
			if (res == s) break;
			cout << res << endl;
			return 0;
		}
	cout << "no" << endl;

	return 0;
}
