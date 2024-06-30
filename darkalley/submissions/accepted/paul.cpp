#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 2e5 + 10, M = 1e6 + 10, MOD = 1e9 + 7;
i64 bita[N], bitb[N], px[N], py[N], inv[M];
    
void update(i64 *bit, int i, int x) {
    for (; i; i -= i & -i) {
        bit[i] = (bit[i] + x) % MOD;
    }
}

i64 get(i64 *bit, int i) {
    i64 res = 0;
    for (i++; i < N; i += i & -i) {
        res = (res + bit[i]) % MOD;
    }
    return res;
}

int main() {
    inv[1] = 1;
    for (int m = 2; m < M; m++) {
        inv[m] = -(MOD/m) * inv[MOD%m] % MOD;
    }

    int n, q;
    double p_;
    cin >> n >> q >> p_;

    int num = llround(1e6 * (1-p_)), denom = 1e6;
    int x = num * inv[denom] % MOD, y = denom * inv[num] % MOD;

    px[0] = py[0] = 1;
    for (int k = 1; k <= n; k++) {
        px[k] = x * px[k-1] % MOD;
        py[k] = y * py[k-1] % MOD;
    }

    while (q--) {
        char c; cin >> c;
        if (c == '?') {
            int i; cin >> i;
            i64 res = (get(bita, i) * py[i] + get(bitb, n-i) * py[n-i]) % MOD;
            if (res < 0) res += MOD;
            cout << res << '\n';
        } else {
            int z, i;
            cin >> z >> i;
            if (c == '-') z = -z;
            update(bita, i+1, z*px[i] % MOD);
            update(bitb, n-i, z*px[n-i] % MOD);
        }
    }
}
