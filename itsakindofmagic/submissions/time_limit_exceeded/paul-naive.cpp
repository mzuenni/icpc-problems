#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 1e6 + 10;
int spf[N];

vector<pair<int,int>> factorize(int n) {
    vector<pair<int,int>> fac;
    while (n > 1) {
        int p = spf[n], k = 0;
        while (spf[n] == p) n /= p, k++;
        fac.emplace_back(p, k);
    }
    return fac;
}

vector<i64> cube_divisors(int n) {
    vector<i64> div = {1};
    for (auto [p, k]: factorize(n)) {
        int m = size(div);
        for (int i = 0; i < 3*m*k; i++) {
            div.push_back(div[i] * p);
        }
    }
    return div;
}

int solve(int n, bool show = false) {
    int res = 0;
    auto div = cube_divisors(n);
    i64 N = i64(n)*n*n;
    for (i64 a: div) {
        for (i64 b: div) {
            if (b == a) continue;
            i64 c = N / a / b;
            if (c == b || c == a) continue;
            if (a*b*c != N) continue;
            for (i64 d: div) {
                if (d == c || d == b || d == a) continue;
                i64 g = N / a / d;
                if (g == d || g == c || g == b || g == a) continue;
                if (a*d*g != N) continue;
                i64 e = N / c / g;
                if (e == g || e == d || e == c || e == b || e == a) continue;
                if (c*e*g != N) continue;
                i64 f = N / d / e;
                if (f == g || f == e || f == d || f == c || f == b || f == a) continue;
                if (d*e*f != N) continue;
                i64 h = N / b / e;
                if (h == g || h == f || h == e || h == d || h == c || h == b || h == a) continue;
                if (b*e*h != N) continue;
                i64 i = N / c / f;
                if (i == h || i == g || i == f || i == e || i == d || i == c || i == b || i == a) continue;
                if (c*f*i != N) continue;
                if (a*e*i != N) continue;
                res++;
                if (show) {
                    cout << a << ' ' << b << ' ' << c << '\n';
                    cout << d << ' ' << e << ' ' << f << '\n';
                    cout << g << ' ' << h << ' ' << i << '\n';
                    cout << '\n';
                }
            }
        }
    }
    return res;
}

i64 sum[N];

int main() {
    iota(spf, spf+N, 0);
    for (int i = 2; i < N; i++) if (spf[i] == i) {
        for (int j = 2*i; j < N; j += i) spf[j] = min(spf[j], i);
    }

    map<vector<int>,int> dp;
    for (int n = 1; n < N; n++) {
        vector<int> a;
        for (auto [_, k]: factorize(n)) a.push_back(k);
        sort(begin(a), end(a));
        if (!dp.count(a)) {
            dp[a] = solve(n);
            cerr << n << ' ' << dp[a] << '\n';
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
