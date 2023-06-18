#include <iostream>
#include <vector>
#include <unordered_map>
#include <string_view>
#include <cassert>

using namespace std;

using ll = long long;
using vll = vector<ll>;

#define sz(a) ((ll)(a).size())

int main() {
	string s;
	cin >> s;

	unordered_map<string_view, ll> labels;
	vll S;
	for (ll i = 0; i < sz(s); i++) {
		assert(s[i] == '(');
		ll j = i+1;
		for (ll c = 1; (c += (s[j] == '(' ? 1 : -1)) > 0; j++) {}

		auto it = labels.emplace( string_view(s).substr(i, 1+j-i), sz(labels) ).first;
		S.emplace_back(it->second);

		i = j;
	}

	if (sz(labels) < 2) {
		cout << "NO";
		return 0;
	}

	vector<string_view> lab(sz(labels));
	for (const auto&[k, v] : labels)
		lab[v] = k;

	for (ll i = 0; i < sz(S); i++)
		cout << lab[S[(i+1)%sz(S)]];
	cout << endl;

	return 0;
}
