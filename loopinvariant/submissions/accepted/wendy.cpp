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
    
    string s; 
    cin >> s;
    
    ll count = 0; 
    for0(i, sz(s)) {
        if(s[i] == '(') count++; 
        else count--;
        if(count == 0 && i != 0 && i != sz(s) - 1) {
            if(s.substr(i + 1).append(s.substr(0, i + 1)) != s) cout << s.substr(i + 1) << s.substr(0, i + 1) << endl; 
            else cout << "no" << endl; 
            return 0; 
        }   
    }
    cout << "no" << endl; 
}
