#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

bool solve(vector<ll> in) {
	in.push_back(0);
	for (ll i = 0, j = 0; i < sz(in); i++) {
		if (j > in[i]) return false;
		if ((in[i] - j) % 2 == 0) {
			j = max(0ll, j - 1);
		} else {
			j++;
		}
	}
	return true;
}

void die(bool res) {
	if (res) cout << "possible" << endl;
	else cout << "impossible" << endl;
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, h;
	cin >> n >> h;
	vector<ll> in(n);
	for (ll& x : in) {
		cin >> x;
		x = h - x;
		if (x < 0) die(false);
	}
	die(solve(in));
}

