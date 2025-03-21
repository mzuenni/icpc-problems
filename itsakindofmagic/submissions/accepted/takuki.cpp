#include <bits/stdc++.h>
using namespace std;

/**
 *  | Y          | 4X - 2Y - Z  | -X + Y + Z |
 *  | Z          | X            | 2X - Z     |
 *  | 3X - Y - Z | -2X + 2Y + Z | 2X - Y     |
 *
 *  (0) AAA   (1) AAB   (2) ABA   (3) ABB   (4) ABC
 *      AAA       CDE       CCC       CDE       ADE
 *      AAA       FGG       DED       FFG       FGE
 *
 *  (5) ABC   (6) ABC   (7) ABC   (8) ABC   (9) ABC
 *      BCA       CAB       DBE       DEC       DEF
 *      CAB       BCA       ABC       DFG       GHI
 */

int main() {
    const vector<string> states = {
        "AAAAAAAAA",
        "AABCDEFGG",
        "ABACCCDED",
        "ABBCDEFFG",
        "ABCADEFGE",
        "ABCBCACAB",
        "ABCCABBCA",
        "ABCDBEABC",
        "ABCDECDFG",
        "ABCDEFGHI",
    };

    auto convert = [&](vector<int>& f) {
        string s;
        map<int, char> mp;
        char c = 'A';
        for (int x : f) {
            if (!mp.count(x)) {
                mp[x] = c;
                c++;
            }
            s += mp[x];
        }
        auto iter = find(states.begin(), states.end(), s);
        assert(iter != states.end());
        return int(iter - states.begin());
    };

    vector merge(10, vector<int>(10));
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            vector<int> f(9);
            for (int i = 0; i < 9; i++) {
                f[i] = states[x][i] * 1000 + states[y][i];
            }
            merge[x][y] = convert(f);
        }
    }

    vector cnt(20, vector<int>(10));
    for (int x = 0; x <= 19; x++) {
        for (int y = 0; y <= 2 * x; y++) {
            for (int z = 0; z <= 2 * x; z++) {
                if (4 * x - 2 * y - z < 0) {
                    continue;
                }
                if (-x + y + z < 0) {
                    continue;
                }
                if (3 * x - y - z < 0) {
                    continue;
                }
                if (-2 * x + 2 * y + z < 0) {
                    continue;
                }
                vector<int> f = {
                    y,
                    4 * x - 2 * y - z,
                    -x + y + z,
                    z,
                    x,
                    2 * x - z,
                    3 * x - y - z,
                    -2 * x + 2 * y + z,
                    2 * x - y,
                };
                cnt[x][convert(f)]++;
            }
        }
    }

    const int N = 1e6 + 10;
    vector<int> lpf(N);
    vector<bool> is_prime(N, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < N; i++) {
        if (!is_prime[i]) {
            continue;
        }
        for (int j = i; j < N; j += i) {
            lpf[j] = i;
            if (i < j) {
                is_prime[j] = false;
            }
        }
    }

    vector dp(N, vector<int>(10));
    dp[1][0] = 1;
    for (int i = 2; i < N; i++) {
        int j = i;
        int k = 0;
        while (j % lpf[i] == 0) {
            j /= lpf[i];
            k++;
        }
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                dp[i][merge[x][y]] += dp[j][x] * cnt[k][y];
            }
        }
    }

    vector<int> pref(N + 1);
    for (int i = 1; i < N; i++) {
        pref[i] = pref[i - 1] + dp[i][9];
    }

    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        cout << pref[llroundl(floorl(cbrtl(n)))] << '\n';
    }
    return 0;
}
