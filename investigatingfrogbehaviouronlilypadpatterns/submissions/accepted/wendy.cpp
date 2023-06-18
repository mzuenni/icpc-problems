#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back

#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll n, q, f; 
    cin >> n; 
    vl frogs(n + 1); 
    set<ll> frogsSet; 
    for(ll i = 1; i < 2'000'000; i++) frogsSet.insert(i);  
    for(ll i = 1; i <= n; i++) {
        cin >> frogs[i];
        frogsSet.erase(frogs[i]); 
    }

    cin >> q; 
    for0(i, q) {
        cin >> f; 
        auto it = frogsSet.lower_bound(frogs[f]);
        ll pos = *it; 
        frogsSet.insert(frogs[f]);  
        // cout << frogs[f] << endl; 
        frogs[f] = pos; 
        frogsSet.erase(pos); 
        cout << pos << endl; 
    }
}