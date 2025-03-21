#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n,q;
  cin>>n>>q;
  vector<ll> c(n+1,1e18), f(n+1), parent(n+1,0), inc = {0};
  rep(i,1,n+1) cin>>c[i];
  for(int i = n; i >= 1; --i) {
    while(c[inc.back()] < c[i]) inc.pop_back();
    parent[i] = inc.back();
    inc.push_back(i);
  }
  rep(i,0,q) {
    char typ;
    int x,q;
    cin>>typ>>x;
    if(typ == '+') {
      cin>>q;
      while(x && q) {
        int k = min<ll>(c[x]-f[x],q);
        f[x] += k;
        q -= k;
        // BUG: below should be an if statement and not a while loop
        while(c[x]==f[x] && c[parent[x]] == f[parent[x]])
          parent[x] = parent[parent[x]];
        x = parent[x];
      }
    }
    else if(typ == '?') {
      cout << f[x] << endl;
    }
    else assert(false);
  }
}
