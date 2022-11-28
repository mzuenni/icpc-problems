#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll inf = 0x3FFFFFFFFFF;

struct seg {
	ll l, r, id;
	bool contains(const seg& o) const {
		return l <= o.l && o.r <= r;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	vector<seg> in(n);
	for (ll i = 0; i < n; i++) {
		ll l, length;
		cin >> l >> length;
		in[i] = {l, l + length, i};
	}
	//assumes sorted
	vector<ll> res(n, 1);
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < i; j++) {
			if (in[j].contains(in[i])) {
				res[in[i].id] = max(res[in[i].id], res[in[j].id] + 1);
			}
		}
	}
	for (ll x : res) cout << x-1 << " ";
	cout << endl;
}
