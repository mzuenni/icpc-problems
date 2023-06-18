#include<bits/stdc++.h>
using namespace std;

int w, h, q;

void assign(int * to, int * from){
    for(int j=0; j<w; j++) to[j] = from[j];
}

bool isId(int * perm){
    for(int j=0; j<w; j++) if(perm[j] != j) return false;
    return true;
}

int id[20];
int tmp[20];
int ra[20];
int rb[20];

struct Tree {
    typedef int * T;
    int s[500000][20]; 
    int n;
    T f(const T a, const T b) { // perm. multiplication
        for(int j=0; j<w; j++) tmp[j] = b[a[j]];
        return tmp;
    } 
    
    Tree(int n, T init) : n(n) {
        for(int i=0; i<2*n; i++) assign(s[i], id);
    }
    
    void update(int i, const T val) {
        for(assign(s[i += n], val); i /= 2;)
            assign(s[i], f(s[i*2], s[i*2+1]));
    }

    T query(int b, int e) { // query [b, e)
        assign(ra, id);
        assign(rb, id);
        for(b += n, e += n; b < e; b /= 2, e /= 2) {
            if(b % 2 != 0) assign(ra, f(ra, s[b++]));
            if(e % 2 != 0) assign(rb, f(s[--e], rb));
        }
        return f(ra, rb);
    }
};

Tree * tree;

void toggle(int h, int x){
    int * p = tree->query(h, h+1);
    if(!isId(p)) tree->update(h, id);
    else{
        for(int j=0; j<w; j++) tmp[j] = j;
        tmp[x] = x+1;
        tmp[x+1] = x;
        tree->update(h, tmp);
    } 
}

void debug_out(const int * perm){
    for(int j=0; j<w; j++) cout << perm[j] + 1 << " ";
    cout << endl;
}

int main(){
    cin >> w >> h >> q;

    for(int j=0; j < w; j++) id[j] = j;
    tree = new Tree(h, id);

    for(int i=0; i<q; i++){
        int y, x1, x2;
        cin >> y >> x1 >> x2;
        x1 = min(x1, x2);
        x1--;
        y--;

        toggle(y, x1);

        int * perm = tree->query(0, h);

        //debug_out(perm);
        int count = 0;
        memset(ra, 0, sizeof(ra));

        for(int j=0; j<w; j++){
            if(ra[j]) continue;
            count++;
            int jj = j;
            while(!ra[jj]){
                ra[jj] = 1;
                jj = perm[jj];
            }
        }
        //cout << count << endl;
        cout << w - count << endl;
    }



}