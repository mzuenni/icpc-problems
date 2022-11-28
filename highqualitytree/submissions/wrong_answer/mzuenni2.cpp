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

ll rem = 0; 

ll dfs(ll u, ll depth, vector<vl> &adj, vector<bool> &vis, vl &countDepth) {
    countDepth[depth]++; 
    vis[u] = true; 
    if(sz(adj[u]) == 1 && u != 0) return depth; 
    ll ind = 0; 
    vl depthChildren = {depth, depth}; 
    for(ll v : adj[u]) {
        if(vis[v]) continue; 
        depthChildren[ind] = dfs(v, depth + 1, adj, vis, countDepth);
        ind++; 
    }
    ll layerToRemove = -1;  
    if(abs(depthChildren[0] - depthChildren[1]) <= 1) return max(depthChildren[0], depthChildren[1]); 
    else if(depthChildren[0] - depthChildren[1] > 1) layerToRemove = depthChildren[0];
    else layerToRemove = depthChildren[1];  

    rem += countDepth[layerToRemove]; 
    countDepth[layerToRemove] = 0; 
    return min(depthChildren[0], depthChildren[1]) + 1;
}


int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll n, a, b; 
    cin >> n;
    vector<vl> adj(n);

    for0(i, n - 1) {
        cin >> a >> b; 
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<bool> vis(n, false);
    vl countDepth(n, 0); 
    dfs(0, 0, adj, vis, countDepth); 
    cout << rem << endl; 

}