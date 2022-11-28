#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(auto i = (a); i < (b); i++)
#define pb push_back
#define fs first
#define sc second
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

const double EPS = 1e-9;

typedef pair<int,ii> iii;


struct node {
    multiset<int> V;
    int mx = 0;
    node() {
        V = {0};
        mx = 0;
    }

    node(int _val) {
        V = {_val};
        mx = _val;
    }

    node(node a, node b) {
        mx = max(a.mx, b.mx);
    }

    void add(int val) {
        V.insert(val);
        if(val > mx) {
            mx = *(--V.end());
        }
    }

    void remove(int val) {
        V.erase(V.find(val));
        if(val == mx) {
            mx = *(--V.end());
        }
    }

};

struct segment_tree {

    int sz, n;

    vector<node> t;
    segment_tree(int _n) : sz(_n*4), n(_n) {
        rep(i,0,sz) t.pb(node(0));
    }

    void build(vi &a, int v=1, int tl=0, int tr=-1) {
        if(tr == -1) tr = n-1;
        if(tl == tr) {
            t[v] = node(a[tl]);
        } else {
            int tm = (tl+tr)/2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = node(t[v*2], t[v*2+1]);
        }
    }

    node query(int l, int r, int v=1, int tl=0, int tr=-1) {
        if(tr == -1) tr = n-1;
        if(l > r) return node(0);
        if(l == tl && r == tr) return t[v];
        int tm = (tl+tr)/2;
        return node(query(l,min(r,tm), v*2, tl, tm),
                query(max(l,tm+1), r, v*2+1, tm+1, tr));

    }

    void add(int pos, int new_val, int v=1, int tl=0, int tr=-1) {
        if(tr == -1) tr = n-1;
        if(tl == tr) {
            t[v].add(new_val);
        }
        else {
            int tm = (tl+tr)/2;
            if(pos <= tm) add(pos, new_val, v*2, tl, tm);
            else add(pos, new_val, v*2+1, tm+1, tr);
            t[v] = node(t[v*2], t[v*2+1]);
        }
    }

    void remove(int pos, int new_val, int v=1, int tl=0, int tr=-1) {
        if(tr == -1) tr = n-1;
        if(tl == tr) {
            t[v].remove(new_val);
        }
        else {
            int tm = (tl+tr)/2;
            if(pos <= tm) remove(pos, new_val, v*2, tl, tm);
            else remove(pos, new_val, v*2+1, tm+1, tr);
            t[v] = node(t[v*2], t[v*2+1]);
        }
    }
};

int main() {
    cin.sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ii> A(n);
    vector<int> ALL;
    for(int i = 0; i < n; i++) {
        cin >> A[i].fs >> A[i].sc;
        A[i].sc = A[i].fs + A[i].sc;
        ALL.pb(A[i].fs);
        ALL.pb(A[i].sc);
    }
    map<int,int> H;
    sort(ALL.begin(), ALL.end());
    int cnt = 0;
    for(int i = 0; i < ALL.size(); i++) {
        if(H.find(ALL[i]) != H.end()) continue;
        H[ALL[i]] = cnt;
        cnt++;
    }

    for(int i = 0; i < n; i++) {
        A[i] = ii(H[A[i].fs], H[A[i].sc]);
    }

    vector<iii> G;
    for(int i = 0; i < n; i++) {
        G.push_back(iii(A[i].fs, ii(-A[i].sc, i)));
        G.push_back(iii(A[i].sc, ii(1, i)));
    }

    sort(G.begin(), G.end());
    segment_tree sq(cnt+1);
    vector<int> ANS(n);
    for(int i = 0; i < 2*n; i++) {
        int index = G[i].sc.sc;
        if(G[i].sc.fs <= 0) {
            int val = sq.query(A[index].sc, cnt).mx;
            sq.add(A[index].sc, val+1);
            ANS[index] = val + 1;
        } else {
            int val = ANS[index];
            sq.remove(A[index].sc, val);
        }
    }
    for(int i = 0; i < n; i++) {
        cout << ANS[i]-1 << " ";
    }
    cout << endl;
}

