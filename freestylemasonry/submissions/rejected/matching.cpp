// @EXPECTED_RESULTS@: TIME_LIMIT_EXCEEDED, RUN_TIME_ERROR
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

vector<vector<int>> adjlist;
// pairs ist der gematchte Knoten oder -1
vector<int> pairs, dist;

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
		if (pairs[v] < 0 ||
			 (dist[pairs[v]] > dist[u] && dfs(pairs[v]))) { 
			pairs[v] = u; pairs[u] = v; 
			return true;
	}}
	dist[u] = -1;
	return false;
}

int hopcroft_karp(int n) { // n = #Knoten links
	int ans = 0;
	pairs.assign(sz(adjlist), -1);
	dist.resize(n);
	// Greedy Matching, optionale Beschleunigung.
	for (int i = 0; i < n; i++) for (int w : adjlist[i])
		if (pairs[w] < 0) {pairs[i] = w; pairs[w] = i; ans++; break;}
	while(bfs(n)) for(int i = 0; i < n; i++)
		if (pairs[i] < 0) ans += dfs(i);
	return ans;
}

bool brute(vector<ll> in) {
	ll n = sz(in);
	in.push_back(0);
	ll sum = 0;
	ll ma = 0;
	for (ll i = 0; i < n; i++) {
		sum += in[i];
		ma = max(ma, in[i]);
	}
	ll nn = n*ma;
	adjlist.assign(nn*2, {});
	auto addEdge = [&](ll x, ll y, ll a, ll b){
		if ((x+y) % 2 != 0) {
			swap(x, a);
			swap(y, b);
		}
		adjlist[x*ma+y].push_back(nn+a*ma+b);
		adjlist[nn+a*ma+b].push_back(x*ma+y);
	};
	for (ll i = 0; i < n; i++ ) {
		for (ll j = 0; j < in[i]; j++) {
			if (j < in[i+1]) addEdge(i, j, i+1, j);
			if (j+1 < in[i]) addEdge(i, j, i, j+1);
		}
	}
	return hopcroft_karp(nn)*2 == sum;
}

void die(bool res) {
	if (res) cout << "possible" << endl;
	else cout << "impossible" << endl;
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, h;
	cin >> n >> h;
	vector<ll> in(n);
	for (ll& x : in) {
		cin >> x;
		x = h - x;
		if (x < 0) die(false);
	}
	die(brute(in));
}

