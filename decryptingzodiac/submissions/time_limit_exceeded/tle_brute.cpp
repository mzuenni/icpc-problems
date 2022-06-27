#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll sigma = 26;

vector<ll> brute(const string& a, const string& b) {
	ll n = sz(a);
	vector<ll> res;
	for (ll dx = 0; dx < n; dx++) {
		for (ll dc = 0; dc < sigma; dc++) {
			res.push_back(0);
			for (ll i = 0; i < n; i++) {
				if (a[i] % sigma == (b[(i+dx) % n] + dc) % sigma) res.back()++;
			}
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	string a, b;
	cin >> n >> a >> b;
	auto res = brute(a, b);
	cout << n-*max_element(all(res)) << endl;
}
