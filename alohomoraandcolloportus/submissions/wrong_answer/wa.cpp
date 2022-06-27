#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

// unions[i] >= 0 => unions[i] =  parent
// unions[i]  < 0 => unions[i] = -height
vector<ll> unions;

void init(ll n) { //Initialisieren
	unions.assign(n, -1);
}

ll findSet(ll n) { // Pfadkompression
	if (unions[n] < 0) return n;
	return unions[n] = findSet(unions[n]);
}

void linkSets(ll a, ll b) { // Union by rank.
	if (unions[a] > unions[b]) unions[a] = b;
	else if (unions[b] > unions[a]) unions[b] = a;
	else {
		unions[a] = b;
		unions[b]--;
}}

void unionSets(ll a, ll b) { // Diese Funktion aufrufen.
	if (findSet(a) != findSet(b)) linkSets(findSet(a), findSet(b));
}

ll n, m;
vector<vector<ll>> adj;

void check(ll x) {
	init(n);
	ll edges = 0;
	for (ll i = 0; i < n; i++) {
		if (i == x) continue;
		ll deg = 0;
		for (ll j : adj[i]) {
			if (j == x) continue;
			deg++;
			if (j > i) continue;
			if (findSet(i) == findSet(j)) return;
			linkSets(i, j);
			edges++;
		}
		if (deg > 2) return;
	}
	if (edges + 1 != n - 1) return;
	cout << "YES" << endl;
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	adj.assign(n, {});
	for (ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	vector<vector<ll>> byDeg;
	for (ll i = 0; i < n; i++) {
		while (sz(byDeg) <= sz(adj[i])) byDeg.push_back({});
		byDeg[sz(adj[i])].push_back(i);
	}
	if (sz(byDeg) > 4) {//there is a vertex with degree > 3
		check(byDeg.back().back());
	} else if (sz(byDeg) == 4) {//there is a vertex with degree 3
		for (ll i = 0; i < n; i++) {
			ll deg3 = 0;
			if (sz(adj[i]) == 3) deg3++;
			for (ll j : adj[i]) {
				if (sz(adj[j]) == 3) deg3++;
			}
			if (deg3 == sz(byDeg[3])) {//vertex is adjacent to all degree 3 vertices
				check(i);
				break;
			}
		}
	} else if (m > 0 && !byDeg[1].empty()) {//there is a vertex with degree 1
		check(byDeg[1][0]);
	} else {//test any vertex
		check(0);
	}
	cout << "NO" << endl;
}
