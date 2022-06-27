#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;

struct Node {
    int col;
    int prio = rand(); //heap key, secondary
    Node* left = nullptr;
    Node* right = nullptr;
    size_t size = 1;

    int lcol,rcol,lrun=1,rrun=1; // stats
    explicit Node (int _col) : col(_col), lcol(_col), rcol(_col) {}
};

size_t size(Node* t) { return t ? t->size : 0; }
int col(Node* t) { return t ? t->col : -1; }
int lcol(Node* t) { return t ? t->lcol : -1; }
int rcol(Node* t) { return t ? t->rcol : -1; }
int lrun(Node* t) { return t ? t->lrun : 0; }
int rrun(Node* t) { return t ? t->rrun : 0; }

void update(Node* t) {
    t->size = 1 + size(t->left) + size(t->right);
    t->lcol = t->left ? t->left->lcol : t->col;
    t->lrun = t->left ? t->left->lrun : 0;
    t->rcol = t->right ? t->right->rcol : t->col;
    t->rrun = t->right ? t->right->rrun : 0;
    if(t->col == t->lcol) {
        t->lrun++;
        if(t->lcol == lcol(t->right)) t->lrun += lrun(t->right);
    }
    if(t->col == t->rcol) {
        t->rrun++;
        if(t->rcol == rcol(t->left)) t->rrun += rrun(t->left);
    }
}

Node* merge(Node* left, Node* right) { // merges two treaps (order is important)
    if(!left || !right) return left ? left : right;
    if(left->prio < right->prio) {
        left->right = merge(left->right, right);
        update(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        update(right);
        return right;
    }
}

pair<Node*,Node*> split_size(Node* t, size_t num) { // (left-)splits off num nodes
    if(!t) return {nullptr, nullptr};
    if(1 + size(t->left) <= num) {
        auto [smaller, larger] = split_size(t->right, num-1u-size(t->left));
        t->right = smaller;
        update(t);
        return {t, larger};
    } else {
        auto [smaller, larger] = split_size(t->left, num);
        t->left = larger;
        update(t);
        return {smaller, t};
    }
}

void del(Node* t) {
    if(!t) return;
    del(t->left);
    del(t->right);
    delete t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n,k,q; cin>>n>>k>>q;

    Node* root = nullptr;
    rep(i,n) {
        int mi; cin>>mi;
        root = merge(root, new Node(mi));
    }

    rep(qq,q) {
        int p,mx; cin>>p>>mx;
        auto [l,r] = split_size(root,p);
        auto m = new Node(mx);
        if(col(m) == lcol(r)) {
            Node *tmp;
            tie(tmp,r) = split_size(r, lrun(r));
            m = merge(m,tmp);
        }
        if(col(m) == rcol(l)) {
            Node *tmp;
            tie(l,tmp) = split_size(l,size(l)-rrun(l));
            m = merge(tmp,m);
        }

        if(size(m)<k) {
            root = merge(l,merge(m,r));
            cout << size(root) << endl;
            continue;
        }

        del(m);
        m = nullptr;

        // merge same in the middle
        while(rcol(l) == lcol(r) && rrun(l)+lrun(r)>=k) {
            Node *ml,*mr;
            tie(l,ml) = split_size(l,size(l)-rrun(l));
            tie(mr,r) = split_size(r,lrun(r));
            del(ml);
            del(mr);
        }

        root = merge(l,r);
        cout << size(root) << endl;
    }

    del(root);

    return 0;
}
