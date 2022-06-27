#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> adj[100010]; // input: adj list
ll curpre=0; // temp: next preorder num
bool articulation[100010]; // output: articulation nodes
ll num[100010];

ll biconnectedDfs(ll i, ll pa){
	ll me = num[i] = ++curpre, top = me, cc = 0;
	bool isan = false;
	for(auto j : adj[i])
		if(pa != j){
			if(num[j]){
				top = min(top,num[j]);
			} else {
				cc++;
				ll up = biconnectedDfs(j, i);
				isan |= pa != -1 && up >= me;
				top = min(top, up);
			}
		}
	isan |= pa==-1 && cc>=2;
	articulation[i] = isan;
	return top;
}

void bicomps(ll n){
	fill_n(num,n,0);
	for(ll i=0; i<n; i++)
		if(num[i]==0)
			biconnectedDfs(i,-1);
}

int main() {
	ll n, m, a, b;
	cin >> n >> m;
	ll deg[n] = {0};
	for (ll i = 0; i < m; ++i) {
		cin >> a >> b;
		++deg[--a];
		++deg[--b];
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	ll one = 0, two = 0, other = 0;
	for (ll i = 0; i < n; ++i) {
		if (deg[i] == 1) ++one;
		else if (deg[i] == 2) ++two;
		else ++other;
	}
	fill_n(num,n,0);
	biconnectedDfs(0,-1);
	for (ll i = 0; i < n; ++i) if (!num[i]) if (one == 2 && other == 1 && deg[i] == 0) {
    cout << "YES" << endl;
		return 0;
	}
	fill_n(num,n,0);
	biconnectedDfs(1,-1);
	for (ll i = 0; i < n; ++i) if (!num[i]) {
		if (one == 2 && other == 1 && deg[i] == 0) cout << "YES" << endl;
		else cout << "NO" << endl;
		return 0;
	}
	bicomps(n);
	for (ll i = 0; i < n; ++i) {
		if (articulation[i]) continue;
		ll _one = 0, _two = 0, _other = 0;
		if (deg[i] == 1) --_one;
		else if (deg[i] == 2) --_two;
		else --_other;
		for (auto x : adj[i]) {
			if (deg[x] == 1) --_one, ++_other;
			else if (deg[x] == 2) --_two, ++_one;
			else if (deg[x] == 3) --_other, ++_two;
		}
		if (one + _one == 2 && other + _other == 0) {
			cout << "YES" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;
	return 0;
}
