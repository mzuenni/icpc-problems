#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;


int main() {
	ll n, w;
	cin >> n >> w;
	getchar();//newline
	for (int i = 0, c; c = getchar(), c != EOF; i++) {
		if (i != 0 && i % w == 0) cout << "\n";
		cout << (char)c;
	}
	cout << endl;
}
