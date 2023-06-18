#include <iostream>
#include <vector>
#include <unordered_map>
#include <string_view>
#include <cassert>
#include <algorithm>

using namespace std;

using ll = long long;
using vll = vector<ll>;

#define sz(a) ((ll)(a).size())
#define all(a) (a).begin(),(a).end()

int main() {
	string s;
	cin >> s;
	ll n = s.size();

	unordered_map<string_view, ll> labels;
	vll S;
	for (ll i = 0; i < n; i++) {
		assert(s[i] == '(');
		ll j = i+1;
		for (ll c = 1; (c += (s[j] == '(' ? 1 : -1)) > 0; j++) {}

		auto it = labels.emplace( string_view(s).substr(i, 1+j-i), sz(labels) ).first;
		S.emplace_back(it->second);

		i = j;
	}
	vector<string_view> lab(sz(labels));
	for (const auto&[k, v] : labels)
		lab[v] = k;

	const auto orig = S;

	for (ll r = 1; r < sz(S); r++) {
		rotate(S.begin(), S.begin()+1, S.end());
		if (orig != S) {
			for (ll i = 0; i < sz(S); i++)
				cout << lab[S[i]];
			cout << endl;

			return 0;
		}
	}
	cout << "no\n";

	return 0;
}
