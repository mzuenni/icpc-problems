#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <charconv>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define REP(i,n) rep(i,0,n)
#define all(v) (v).begin(), (v).end()
#define rs resize
#define DBG(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl

const ld PI = acos(-1.0);
template<class T> using min_queue =
priority_queue<T, vector<T>, greater<T>>;
template<class T> int sz(const T &x) {
    return (int) x.size(); // copy the ampersand(&)!
}

// START OF ACTUAL PROGRAM, START READING HERE

void run() {
	ll m = 1000000;
	vi A(m+1, 1), B(m+1, 1), C(m+1, 1), D(m+1, 1), E(m+1, 1);
	vector<bool> isPrime(m+1, true);
	isPrime[0] = false;
	isPrime[1] = false;

	for (ll i = 1; i <= m; i++) {
		if (!isPrime[i]) continue;
		ll c = 0, pow = 1;
		while (pow*i <= m) {
			c++;
			pow *= i;
		}
		while (c > 0) {
			for (ll j = pow; j <= m; j += pow) {
				if (j%(pow*i) == 0) continue;
				isPrime[j] = false;
				A[j] *= 2*c*c+2*c+1;
				B[j] *= 2*(c/3)+1;
				C[j] *= 2*(c/2)+1;
				D[j] *= 2*c+1;
				E[j] *= 1;
			}
			pow /= i;
			c--;
		}
		isPrime[i] = true;
	}

	for (ll i = 1; i <= m; i++) {
		B[i] -= E[i];
		C[i] -= E[i];
		D[i] -= E[i];
		A[i] -= 4*B[i]+2*C[i]+2*D[i]+E[i];
	}

	vi R(m+1, 0);
	for (ll i = 1; i <= m; i++) {
		R[i] = R[i-1] + A[i];
	}

	ll t;
	cin >> t;
	for (ll i = 0; i < t; i++) {
		ll n;
		cin >> n;
		cout << R[(ll) cbrt((ld) n)] << endl;
	}
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
    run();
    return 0;
}
