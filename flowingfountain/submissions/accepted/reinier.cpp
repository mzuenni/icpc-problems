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
#include <stack>

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

struct dsu {
	vi p;
	vi r;
	dsu(int n) : p(n, -1), r(n, 0) {
		for (ll i = 0; i < n; i++) {
			r[i] = i;
		}
	}
	int find(int i) {
		return p[i] < 0 ? i : p[i] = find(p[i]); }
	void unite(int a, int b) {
		if ((a = find(a)) == (b = find(b))) return;
		if (p[a] > p[b]) swap(a,b);
		p[a] += p[b]; p[b] = a;
		r[a] = max(r[a], r[b]);
	}
	int root(int i) {
		return r[find(i)];
	}
};

void run() {
	ll n, q;
	cin >> n >> q;
	vi C(n), R(n);
	for (ll i = 0; i < n; i++) {
		cin >> C[i];
	}
	vi N(n);
	stack<ll> S;
	for (ll i = n-1; i >= 0; i--) {
		while (!S.empty() && C[S.top()] <= C[i]) S.pop();
		if (S.empty()) N[i] = n;
		else N[i] = S.top();
		S.push(i);
	}
	
	dsu D(n+1);
	for (ll i = 0; i < q; i++) {
		string t;
		cin >> t;
		if (t[0] == '+') {
			ll l, x;
			cin >> l >> x;
			l--;
			while (l < n && x > 0) {
				ll y = min(x, C[l]);
				C[l] -= y;
				R[l] += y;
				x -= y;
				if (C[l] == 0) {
					D.unite(l, N[l]);
				}
				l = D.root(l);
			}
		} else {
			ll l;
			cin >> l;
			cout << R[l-1] << endl;
		}
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
