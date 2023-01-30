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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t, n;
    cin >> t;
    ll a;
    for0(i, t) {
        cin >> n;
        multiset<ll> c;
        for0(i, n) {
            cin >> a;
            c.insert(a);
        }
        ll count = 0;
        while(sz(c) >= 3) {
            ll x = *c.begin();
            ll fst = *prev(c.end());
            c.erase(prev(c.end()));
            ll snd = *prev(c.end());
            c.erase(prev(c.end()));
            c.insert(fst + snd + 1);
            c.erase(c.begin());
            if(x > 1) c.insert(x - 1);
            count++;
        }
        if(sz(c) == 1) cout << count + 1 << endl;
        else if(sz(c) == 2 && *c.begin() == 1) cout << count + 1 << endl;
        else cout << count + 2 << endl;

    }
}