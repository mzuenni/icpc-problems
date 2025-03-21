#include <vector>
#include <iostream>
#include <stack>

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

vl parent;

ll find(ll x) {
    if (parent[x] == x) return x;
    else {
        parent[x] = find(parent[x]);
        return parent[x];
    }
}

void un(ll x, ll y) {
    ll a = find(x);
    ll b = find(y);
    if (a == b) return;
    else parent[a] = b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, q, l, x;
    char t;
    cin >> n >> q;
    vl cap(n + 1), water(n + 1, 0), next(n);
    cap[n] = (ll) 1e18;
    parent.resize(n + 1);
    for0(i, n + 1) parent[i] = i;

    stack<ll> s;
    for0(i, n + 1) {
        if (i != n) cin >> cap[i];
        while (!s.empty() && cap[s.top()] < cap[i]) {
            next[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    for0(i, q) {
        cin >> t >> l;
        l--;
        if (t == '?') cout << water[l] << endl;
        else {
            cin >> x;
            ll level = find(l);
            while (x > 0 && water[level] + x >= cap[level]) {
                x -= cap[level] - water[level];
                water[level] = cap[level];
                un(level, next[level]);
                level = find(next[level]);
            }
            water[level] += x;
        }
    }
}