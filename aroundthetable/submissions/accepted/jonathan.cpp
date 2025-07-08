#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
using pll = pair<ll, ll>;

#define TS ll ts; cin >> ts; while (ts--)
#define all(x) ::begin(x), ::end(x)
constexpr ll INF = 1e18;

ll n, l, r;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> l >> r;
	n = l + r;

	ll res = 2 * n;
	if (2 * r + 0 == n) res -= r;
	if (2 * r + 1 == n) res /= 2;
	if (2 * r + 2 == n) res -= n / 2;
	cout << res << '\n';
	
	return 0;
}
