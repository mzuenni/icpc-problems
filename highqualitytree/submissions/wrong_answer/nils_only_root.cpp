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

vi f1, f2;

void dfs(int i, int par, int depth, vi &f){
    f[depth]++;
    trav(y, graph[i]){
        if(y != par){
            dfs(y, i, depth+1, f);
        }
    }
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
    rep(c1,0,n){
        f1.push_back(0);
        f2.push_back(0);
        assert(sz(graph[c1]) <= 3);
    }
    
    if(sz(graph[0]) > 0)dfs(graph[0][0],0,0,f1);
    if(sz(graph[0]) == 2)dfs(graph[0][1],0,0,f2);
    
    while(sz(f1) > 0 && f1.back() == 0){
        f1.pop_back();
    }
    while(sz(f2) > 0 && f2.back() == 0){
        f2.pop_back();
    }
    if(sz(f1) > sz(f2))swap(f1,f2);
    while(sz(f2) > sz(f1)+1){
        f2.pop_back();
    }
    int sum = 1;
    trav(y, f1){
        sum += y;
    }
    trav(y, f2){
        sum += y;
    }

    cout << n-sum << "\n";

    return 0;
}