#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 2e5 + 10, K = 666, MOD = 1e9 + 7;
i64 val[N], add[N], px[N];

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
            if (int(updates.size()) > K) {
                for (auto [z, j]: updates) {
                    add[j] = (add[j] + z) % MOD;
                }

                i64 cur = 0;
                for (int i = 1; i <= n; i++) {
                    cur = (cur + add[i]) % MOD;
                    val[i] = (val[i] + cur) % MOD;
                    cur = cur * x % MOD;
                }
                cur = 0;
                for (int i = n; i >= 1; i--) {
                    val[i] = (val[i] + cur) % MOD;
                    cur = (cur + add[i]) % MOD;
                    cur = cur * x % MOD;
                }

                for (auto [z, j]: updates) {
                    add[j] = 0;
                }
                updates.clear();
            }

            int i; cin >> i;
            i64 res = val[i];
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
