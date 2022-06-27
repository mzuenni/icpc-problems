#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cassert>

using namespace std;

#define sz(a) ll((a).size())
#define all(a) (a).begin(),(a).end()

using ll = long long;
using vll = vector<ll>;

constexpr ll MAXN = 755;

ll matchedTo[MAXN];
bitset<MAXN> vis;
vll adj[MAXN]; // sufficient to add edges in one direction

bool dfs(ll i) {
	ll ls = matchedTo[i];
	if (ls == -1) return true;
	if (vis[i]) return false;
	vis[i] = true;
	for (ll j : adj[ls])
		if (dfs(j)) {
			matchedTo[matchedTo[j] = ls] = j;
			return true;
		}
	return false;
}
ll maxMatching(ll n) {
	fill_n(matchedTo,n,-1);
	ll res = 0;
	for (ll i=0; i<n; i++)
		if (matchedTo[i] == -1) {
			vis.reset();
			for (ll j : adj[i])
				if (dfs(j)) {
					matchedTo[matchedTo[j] = i] = j;
					res++;
					break;
				}
		}
	return res;
}

int main() {
	ll n; cin >> n;

	vll a;
	bool one = false;
	for (ll i = 0, x; i < n && cin >> x; i++) {
		if (x != 1 || !one) a.emplace_back(x);
		one |= x == 1;
	}
	n = sz(a);

	vector<bool> is_prime(2 * *max_element(all(a)) + 1, true);
	is_prime[0] = is_prime[1] = false;
	for (ll p = 2; p < sz(is_prime); p++)
		if (is_prime[p])
			for (ll j = p*p; j < sz(is_prime); j += p)
				is_prime[j] = false;


	for (ll i = 0; i < n; i++)
		if (a[i] % 2 == 0)
			for (ll j = 0; j < n; j++)
				if (is_prime[a[i]+a[j]])
					adj[i].emplace_back(j);

	cout << n - maxMatching(n) << endl;

	return 0;
}
