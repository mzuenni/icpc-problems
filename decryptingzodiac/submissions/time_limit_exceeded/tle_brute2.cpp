#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")

#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr char sigma = 26;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	string a, b;
	cin >> n >> a >> b;
	a += a;
	int res = n;
	std::array<int, 2*sigma> tmp;
	for (int i = 0; i < n; i++){
		tmp.fill(0);
		for (int j = 0; j < n; j++) {
			tmp[a[i+j]-b[j]+sigma]++;
		}
		int ma = 0;
		for (char j = 0; j < sigma; j++) {
			ma = max(ma, tmp[j]+tmp[j+sigma]);
		}
		res = min(res,n-ma);
	}
	cout << res << endl;
}
