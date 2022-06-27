#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200000;
vector<int> adj[MAXN];
vector<int> adj2[MAXN];
bool flags[MAXN];
int n, m;

vector<int> tmp;

void dfs(int i){
    if(flags[i]) return;
    flags[i] = true;
    for(int j  : adj2[i]) dfs(j);
}

bool isConnected(){
    //cerr << "testing connectivity..." << endl;
    memset(flags, 0, sizeof(flags));
    dfs(0);
    for(int i=0; i<n; i++) if(!flags[i]) return false;
    return true;
}

bool canBeOpenedAt(int h){
    //cerr << "trying to open at " << h << endl;
    memset(flags, 0, sizeof(flags));
    for(int i : adj[h]) flags[i] = true;

    for(int i=0; i<n; i++) adj2[i].clear();

    for(int i=0; i<n; i++){
        if(i == h) continue;
        //cerr << i << " has " << adj[i].size() << " neighbours" << endl;

        if(adj[i].size() == 0) return false;
        else if(adj[i].size() == 1){
            if(flags[i]) return false;
            for(int j : adj[i]) adj2[i].push_back(j);
            adj2[i].push_back(h);
            adj2[h].push_back(i);
        }
        else if(adj[i].size() == 3){
            if(!flags[i]) return false;
            for(int j : adj[i]) if(j != h) adj2[i].push_back(j);
        } 
        else if(adj[i].size() == 2){
            adj2[i].push_back(adj[i][0]);
            adj2[i].push_back(adj[i][1]);
            if(adj[i][0] == h ||adj2[i][1] == h) adj2[h].push_back(i);

        }
        else if(adj[i].size() > 3) return false;
    }
    return isConnected();
}

bool solve(){
    // count degree-4 vertices
    tmp.clear();
    for(int i=0; i<n; i++){
        if(adj[i].size() >= 4) tmp.push_back(i);
    } 
    //cerr << "there are " << tmp.size() << " deg-4-or-higher vertices" << endl;

    if(tmp.size() > 1) return false;
    if(tmp.size() == 1) return canBeOpenedAt(tmp[0]);
    
    // count degree-3 vertices
    tmp.clear();
    for(int i=0; i<n; i++){
        if(adj[i].size() >= 3) tmp.push_back(i);
    } 
    //cerr << "there are " << tmp.size() << " deg-3 vertices" << endl;

    if(!tmp.empty()){
        vector<pair<int, bool>> candidates;
        candidates.push_back({tmp[0], true});
        for(int j : adj[tmp[0]]) candidates.push_back({j, true});

        for(int i : tmp) {
            set<int> s;
            s.insert(i);
            for(int j : adj[i]) s.insert(j);
            for(pair<int, bool> p : candidates) if(!s.count(p.first)) p.second = false;
        } 

        for(pair<int, bool> p : candidates) {
            if(p.second && canBeOpenedAt(p.first)) return true;
        }
        return false;
    }

    // count degree-0 vertices
    tmp.clear();
    for(int i=0; i<n; i++){
        if(adj[i].empty()) tmp.push_back(i);
    } 
    //cerr << "there are " << tmp.size() << " deg-0 vertices" << endl;

    if(tmp.size() > 1) return false;
    if(tmp.size() == 1) return canBeOpenedAt(tmp[0]);

    // count degree-1 vertices
    tmp.clear();
    for(int i=0; i<n; i++){
        if(adj[i].size() == 1) tmp.push_back(i);
    } 
    //cerr << "there are " << tmp.size() << " deg-0 vertices" << endl;
    if(tmp.size() > 2) return false;
    for(int i : tmp) if(canBeOpenedAt(i)) return true;

    return canBeOpenedAt(0);
}

int main(){
    cin >> n >> m;

    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }


    if(solve()) cout << "YES" << endl;
    else cout << "NO" << endl;
}
