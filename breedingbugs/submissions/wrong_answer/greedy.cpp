#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll N = 20000007;
bitset<N / 2> isNotPrime;

bool isPrime(ll x) {
	if (x < 2 || x % 2 == 0) return x == 2;
	else return !isNotPrime[x / 2];
}

void primeSieve() {
	// i * i < N is enough for isPrime
	for (ll i = 3; i < N; i += 2) {
		if (!isNotPrime[i / 2]) {
			for (ll j = i * i; j < N; j+= 2 * i) {
				isNotPrime[j / 2] = 1;
			}
		}
	}
}


vector<vector<int>> adjlist;
vector<int> pairs;

int match(int n) { // n = #Knoten links
	int ans = 0;
	pairs.assign(sz(adjlist), -1);
	// Greedy Matching, optionale Beschleunigung.
	for (int i = 0; i < n; i++) {
		for (int w : adjlist[i]) {
			if (pairs[w] < 0) {
				pairs[i] = w;
				pairs[w] = i;
				ans++;
				break;
			}
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	vector<vector<ll>> in(2);
	bool seenOne = false;
	for (ll i = 0; i < n; i++) {
		ll x;
		cin >> x;
		if (x != 1 || !seenOne) in[x % 2].push_back(x);
		seenOne |= x == 1;
	}

	primeSieve();
	adjlist.assign(n, {});
	for (ll i = 0; i < sz(in[0]); i++) {
		for (ll j = 0; j < sz(in[1]); j++) {
			if (isPrime(in[0][i] + in[1][j])) {
				adjlist[i].push_back(sz(in[0]) + j);
				adjlist[sz(in[0]) + j].push_back(i);
			}
		}
	}

	cout << sz(in[0])+sz(in[1])-match(sz(in[0])) << endl;
}
