#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 2e5 + 10, MOD = 1e9 + 7;
i64 px[N];

int main() {

    int n, q;
    double p_;
    cin >> n >> q >> p_;

    int x = llround(1e6 * (1-p_)) * 142'857'001 % MOD;
    px[0] = 1;
    for (int k = 1; k <= n; k++) {
        px[k] = x * px[k-1] % MOD;
    }

    vector<pair<int,int>> updates;
    while (q--) {
        char c; cin >> c;
        if (c == '?') {
            int i; cin >> i;
            i64 res = 0;
            for (auto [z, j]: updates) {
                res = (res + z * px[abs(i-j)]) % MOD;
            }
            if (res < 0) res += MOD;
            cout << res << '\n';
        } else {
            int z, i;
            cin >> z >> i;
            if (c == '-') z = -z;
            updates.emplace_back(z, i);
        }
    }
}
