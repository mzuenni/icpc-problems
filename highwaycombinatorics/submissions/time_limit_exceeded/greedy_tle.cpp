#include <bits/stdc++.h>
using namespace std;
 
#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()
 
using ll = long long;
using ld = long double;

constexpr ll mod = 1000000007;
constexpr ll lim = 200;

constexpr ll fibsLim = 89;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<ll> fibs = {1, 1};
	for (ll i = 0; i <= fibsLim; i++) {
		fibs.push_back(fibs[i] + fibs[i + 1]);
	}
	ll x;
	cin >> x;
	if (x == 0) {
		cout << ".##" << endl;
		cout << "##." << endl;
	} else {
		for (ll i = 0;; i++) {
			ll y = x + i*mod;
			vector<ll> res;
			for (ll j = sz(fibs) - 1; j >= 2; j--) {
				while (y % fibs[j] == 0) {
					res.push_back(j);
					y /= fibs[j];
				}
			}
			if (y == 1) {
				if (res.empty()) res.push_back(0);
				string out;
				for (ll z : res) {
					out += string(z, '.');
					out += '#';
				}
				out.pop_back();
				cout << out << endl;
				cout << out << endl;
				return 0;
			}
		}
	}
}
