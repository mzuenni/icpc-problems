#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)
#define pb push_back
#define sz(x) (ll)(x).size()

using namespace std;
using pl = pair<long long, long long>;
using ll = long long;
using ld = long double;
using vl = vector<long long>;
using vi = vector<int>;

int main() {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    c /= gcd(c, d);
    d /= gcd(c, d);
    bool swapped = false;
    if(c > d) {
        swap(c, d);
        swap(a, b);
        swapped = true;
    }
    string stra = to_string(a);
    string strb = to_string(b);

    for0(i, (1 << sz(stra))) {
        ll newa = 0;
        vl delDigits(10, 0);
        for0(ind, sz(stra)) {
            if(i & (1 << ind)) newa = (newa * 10) + (stra[ind] - '0');
            else delDigits[stra[ind] - '0']++;
        }
        if(newa == 0 || newa > ((1ll << 62) / d) * c) continue;
        if(((newa % c) * (d % c)) % c != 0) continue;

        string newb = to_string((newa * d) / c);
        ll ind = 0;
        for0(k, sz(strb)) {
            if(ind < sz(newb) && strb[k] == newb[ind]) ind++;
            else delDigits[strb[k] - '0']--;
        }

        if(ind < sz(newb)) continue;
        else {
            bool poss = true;
            for(ll x : delDigits) {
                if(x != 0) poss = false;
            }
            if(!poss) continue;
            else {
                cout << "possible" << endl;
                ll bprime = stoll(newb);
                if(swapped) swap(newa, bprime);
                cout << newa << " " << bprime << endl;
                return 0;
            }
        }
    }
    cout << "impossible" << endl;

}