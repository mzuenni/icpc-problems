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

ll INF = (ll) 1e10;

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    string s;
    cin >> s;
    string x = s;
    sort(x.begin(), x.end());
    string perm;
    for0(i, sz(s)) {
        if (i == 0 || x[i] != perm.back()) perm.pb(x[i]);
    }

    ll res = INF;

    do {
        vector<vl> dp(sz(s) + 1, vl(sz(perm) + 1, INF));
        dp[0] = {0, 0, 0, 0, 0};
        for0(i, sz(s)) {
            for0(j, sz(perm)) {
                dp[i + 1][j + 1] = min(dp[i][j], dp[i][j + 1]) + (perm[j] != s[i]);
            }
        }
        res = min(res, *min_element(dp[sz(s)].begin(), dp[sz(s)].end()));
    } while(next_permutation(perm.begin(), perm.end()));

    cout << res << endl;
}
