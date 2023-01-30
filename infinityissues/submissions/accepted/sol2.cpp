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

	ll n, w;
	cin >> n >> w;
	string s;
	for (ll i = 0; i < n; i++) {
		string c;
		cin >> c;
		s += c;
		s += ' ';
	}
	s.pop_back();
	for (int i = 0; i < sz(s); i++) {		
		if (i != 0 && i % w == 0) cout << "\n";
		cout << s[i];
	}
}
