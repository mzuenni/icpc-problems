#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>
using namespace std;
using i64 = long long;

const int N = 1e6 + 10, K = 25;
int spf[N];

int total[K];
map<pair<int,int>,int> by_dir[K];

vector<pair<int,int>> factorize(int n) {
    vector<pair<int,int>> fac;
    while (n > 1) {
        int p = spf[n], k = 0;
        while (spf[n] == p) n /= p, k++;
        fac.emplace_back(p, k);
    }
    return fac;
}

vector<pair<int,int>> directions = {{0, 1}, {1, -2}, {1, -1}, {1, 0}, {1, 1}, {1, 2}, {2, -1}, {2, 1}};

int solve(vector<int> a) {
    if (a.empty()) return 0;

    int res = 1;
    for (int k: a) res *= total[k];

    for (auto pr: directions) {
        int cur = 1;
        for (int k: a) cur *= by_dir[k][pr] + 1;
        res -= cur;
    }
    res += 7;
    return res;
}

i64 sum[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    iota(spf, spf+N, 0);
    for (int i = 2; i < N; i++) if (spf[i] == i) {
        for (int j = 2*i; j < N; j += i) spf[j] = min(spf[j], i);
    }

    for (int c = 0; c < K; c++) {
        for (int a = -c; a <= c; a++) {
            for (int b = -c; b <= c; b++) {
                if (abs(a)+abs(b) > c) continue;
                int g = max(abs(gcd(a, b)), 1);
                int x = a/g, y = b/g;
                if (x < 0 || (x == 0 && y < 0)) x = -x, y = -y;
                total[c]++;
                by_dir[c][make_pair(x, y)]++;
            }
        }
    }

    map<vector<int>,int> dp;
    for (int n = 1; n < N; n++) {
        vector<int> a;
        for (auto [_, k]: factorize(n)) a.push_back(k);
        sort(begin(a), end(a));
        if (!dp.count(a)) {
            dp[a] = solve(a);
        }
        sum[n] = dp[a] + sum[n-1];
    }

    int tc; cin >> tc;
    while (tc--) {
        i64 n; cin >> n;
        int r = cbrtl(n);
        cout << sum[r] << '\n';
    }
}
