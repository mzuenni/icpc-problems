#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef vector<int> vi;

const int MAXN = 200001;
vector<vi> graph(MAXN, vi());
int n;

vi solve(int i, int par){
    vi res = {1};

    vi f1 = {};
    vi f2 = {};
    
    trav(y, graph[i]){
        if(y != par){
            vi tmp = solve(y, i);
            if(sz(f1) == 0){
                f1 = tmp;
            }
            else{
                f2 = tmp;
            }
        }
    }
    if(sz(f1) > sz(f2))swap(f1,f2);
    trav(y, f1){
        res.push_back(y);
    }
    if(sz(f2) != sz(f1))res.push_back(0);
    rep(c1,0,min(sz(f2), sz(f1)+1)){
        res[c1+1] += f2[c1];
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    rep(c1,0,n-1){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vi ans = solve(0,-1);
    int sum = 0;
    trav(y, ans){
        sum += y;
    }
    cout << n-sum << "\n";
    
    return 0;
}