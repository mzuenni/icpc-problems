#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

ll eval(const vector<pair<ll, ll>>& in) {
	ll cost = 1;
	ll res = 0;
	for (auto e : in) {
		res += cost * e.first;
		cost += e.second;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, m;
	cin >> n >> m;
	vector<pair<ll, ll>> in(n);
	for (ll i = 0; i < n; i++) {
		ll a, b;
		cin >> a >> b;
		in[i] = {a, b};
	}
	sort(all(in), [](const pair<ll, ll>& a, const pair<ll, ll>& b){
		return a.first + (1+a.second)*b.first < b.first + (1+b.second)*a.first;
	});
	cout << eval(in) << endl;
}
