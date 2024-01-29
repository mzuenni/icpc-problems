#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;
	vector<pair<ll, ll>> in(n);
	for (auto& [a,b] : in) cin >> a >> b;
	sort(all(in), [](auto a, auto b){
		return a.first*a.second > b.first*b.second;
	});
	cout << in[0].first*in[0].second*min(in[0].first,in[0].second) << endl;
}
