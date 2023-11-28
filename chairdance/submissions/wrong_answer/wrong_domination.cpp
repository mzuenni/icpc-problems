//g++ -std=c++14 -Wall -Wextra -Wconversion -Wshadow -pedantic -O2 

#include <bits/stdc++.h>
using namespace std;

#define fora(i, n) for(int i = 0; i < n; ++i)
#define forb(i, n) for(int i = 1; i <= n; ++i)
#define pb push_back
#define eb emplace_back
#define sz(x) (int) (x).size()
#define all(x) (x).begin(), (x).end()

using ll = long long;
using ld = long double;
using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;

ll gcd(ll a, ll b) {return b == 0 ? a : gcd(b, a % b);}

// a*x + b*y = ggt(a, b)
ll extendedEuclid(ll a, ll b, ll& x, ll& y) {
    if (a == 0) {x = 0; y = 1; return b;}
    ll x1, y1, d = extendedEuclid(b % a, a, x1, y1);
    x = y1 - (b / a) * x1; y = x1;
    return d;
}

int main() {
    std::ios::sync_with_stdio(false);

    ll mod, q, v, w, x;
    cin >> mod >> q;
    ll a = 1;
    ll b = 0; // x -> a*x + b
    char c;
    fora(_, q){
        cin >> c >> x;
        if(c == '+'){
            b = (b + x) % mod;
        } else if (c == '*'){
            b = (b * x) % mod;
            a = (a * x) % mod;
        } else {
            ll y = (x - b + mod) % mod;
            if (gcd(y, mod) % gcd(a, mod) != 0) cout << -1 << endl;
            else {
                ll g1 = extendedEuclid(a, mod, v, w);
                ll res = ((((y / g1) * v) % mod + mod) % mod) % (mod / g1);
                if(res == 0) res += mod / g1;
                cout << res << endl;
            }
        }
    }    

}

