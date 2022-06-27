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
vector<int> pairs, dist; // pairs ist der gematchte Knoten oder -1

bool bfs(int n) {
	queue<int> q;
	for(int i = 0; i < n; i++) {
		if (pairs[i] < 0) {dist[i] = 0; q.push(i);}
		else dist[i] = -1;
	}
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : adjlist[u]) {
			if (pairs[v] < 0) return true;
			if (dist[pairs[v]] < 0) {
				dist[pairs[v]] = dist[u] + 1;
				q.push(pairs[v]);
	}}}
	return false;
}

bool dfs(int u) {
	for (int v : adjlist[u]) {
		if (pairs[v] < 0 || (dist[pairs[v]] > dist[u] && dfs(pairs[v]))) { 
			pairs[v] = u; pairs[u] = v; 
			return true;
		}
	}
	dist[u] = -1;
	return false;
}

int hopcroft_karp(int n) { // n = #Knoten links
	int ans = 0;
	pairs.assign(sz(adjlist), -1);
	dist.resize(n);
	while(bfs(n)) {
		for(int i = 0; i < n; i++) {
			if (pairs[i] < 0) ans += dfs(i);
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

	cout << sz(in[0])+sz(in[1])-hopcroft_karp(sz(in[0])) << endl;
}
