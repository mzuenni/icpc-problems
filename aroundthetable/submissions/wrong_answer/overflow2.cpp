#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int sol(int l, int r) {
	int n = l + r;
	if (l < r || l > r + 2) return 2*n;
	if (n % 2 == 0) return n + n / 2;
	return n;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int l, r;
	cin >> l >> r;
	cout << sol(l, r) << endl;
}
