
// freopen("../../p8.t4.in", "r", stdin);

#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;


struct Node {
    int prio; //heap key, secondary
    Node* left = nullptr;
    Node* right = nullptr;
    size_t size = 1;
    int csize, col, cnt;
    explicit Node (int _col, int _cnt) : prio(rand()), csize(_cnt), col(_col), cnt(_cnt) {}
};

size_t size(Node* t) { return t ? t->size : 0; }
int csize(Node* t) { return t ? t->csize : 0; }
int col(Node* t) { return t ? t->col : -1; }

void update(Node* t) {
    t->size = 1 + size(t->left) + size(t->right);
    t->csize = t->cnt + csize(t->left) + csize(t->right);
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

pair<Node*,Node*> split(Node* t, int num) { // (left-)splits off nodes with <= num summed cnt
    if(!t) return {nullptr, nullptr};
    auto left_cnt = t->cnt + csize(t->left);
    if(left_cnt <= num) {
        auto [smaller, larger] = split(t->right, num-left_cnt);
        t->right = smaller;
        update(t);
        return {t, larger};
    } else {
        auto [smaller, larger] = split(t->left, num);
        t->left = larger;
        update(t);
        return {smaller, t};
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

template<class F>
void trav(Node* t, F&& f) {
    if(!t) return;
    trav(t->left,f);
    f(t);
    trav(t->right,f);
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
    Node* last = nullptr;
    rep(i,n) {
        int mi; cin>>mi;
        if(col(last) == mi) {
            last->cnt++;
            last->csize++;
        } else {
            root = merge(root, last);
            last = new Node(mi,1);
        }
    }
    root = merge(root, last);

    rep(qq,q) {
        int p,mx; cin>>p>>mx;
        Node *l,*m,*r;
        tie(l,r) = split(root,p);
        tie(m,r) = split_size(r,1);
        if(col(m)==mx) { // merge new into m
            m->cnt++; m->csize++;
            if(m->cnt<k) r = merge(m,r);
            else delete m;
        } else if(p==csize(l)) { // put new before m
            r = merge(merge(new Node(mx,1), m), r);
        } else { // split m and insert new somewhere in between
            assert(m);
            assert(csize(l)<p);
            assert(csize(l) + csize(m)>p);
            auto ml = new Node(m->col, p-csize(l));
            m->cnt -= p-csize(l), m->csize = m->cnt;
            r = merge(merge(merge(ml,new Node(mx,1)), m),r); // r = (ml, mx, m, r)
        }

        // merge same in the middle
        while(size(l) && size(r)) {
            Node *ml,*mr; // we got [l, ml, mr, r] where ml and mr are just 1 elems
            tie(l,ml) = split_size(l,size(l)-1);
            tie(mr,r) = split_size(r,1);
            if(col(ml)!=col(mr)) {
                l = merge(l,ml);
                r = merge(mr,r);
                break;
            }

            ml->cnt += mr->cnt;
            ml->csize += mr->csize;
            delete mr;
            if(ml->cnt<k) {
                merge(l,ml);
                break;
            }
            delete ml;
        }

        root = merge(l,r);

        cout << csize(root) << endl;
    }

    // for debug
    // trav(root, [](Node* t) { cout << t->col << ' ' << t->cnt << endl; });

    del(root);

    return 0;
}

