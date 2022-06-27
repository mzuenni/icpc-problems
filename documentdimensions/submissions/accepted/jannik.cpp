#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

#define all(a) (a).begin(),(a).end()


int main() {
	ll n; cin >> n;
	vector<ll> w(n);
	for (ll& x : w) {
		string s;
		cin >> s;
		x = s.size();
	}
	vector<ll> pfx(n+1);
	for (ll s = 0, i = 0; i < n; i++)
		pfx[i + 1] = (s += w[i] + 1);
	
	ll res = LLONG_MAX;

	for (ll s = *max_element(all(w)); s <= pfx.back(); s++) {
		ll i = 0, lines = 0;
		while (i < n) {
			lines++;
			if (lines + s >= res) { lines = res; break; }
			ll j = upper_bound(pfx.begin()+i+1, pfx.end(), pfx[i] - 1 + s) - pfx.begin();
			if (j - i > 1 && j <= n && pfx[j] - pfx[i] - 1 > s) j--;
			i = j;
		}
		res = min(res, lines + s);
	}
	
	cout << res << endl;

	return 0;
}
