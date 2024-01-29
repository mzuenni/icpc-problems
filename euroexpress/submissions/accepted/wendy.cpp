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
    ll n, a, b; 
    cin >> n; 
    ll best = 0; 
    for0(i, n) {
        cin >> a >> b;
        best = max(best, a * b * min(a,b));  
    }
    cout << best << endl; 
}