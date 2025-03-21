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
    i64 e = n;
    for (i64 a: div) {
        if (a == e) continue;
        i64 i = N / a / e;
        if (i == a || i == e) continue;
        if (a*e*i != N) continue;
        for (i64 b: div) {
            if (b == a || b == e || b == i) continue;
            i64 c = N / a / b;
            if (c == a || c == b || c == e || c == i) continue;
            if (a*b*c != N) continue;
            i64 g = N / c / e;
            if (g == a || g == b || g == c || g == e || g == i) continue;
            if (c*e*g != N) continue;
            i64 h = N / g / i;
            if (h == a || h == b || h == c || h == e || h == g || h == i) continue;
            if (g*h*i != N) continue;
            if (b*e*h != N) continue;
            i64 d = N / a / g;
            if (d == a || d == b || d == c || d == e || d == g || d == h || d == i) continue;
            if (a*d*g != N) continue;
            i64 f = N / d / e;
            if (f == a || f == b || f == c || f == d || f == e || f == g || f == h || f == i) continue;
            if (c*f*i != N) continue;
            if (d*e*f != N) continue;
            res++;
            if (show) {
                cout << a << ' ' << b << ' ' << c << '\n';
                cout << d << ' ' << e << ' ' << f << '\n';
                cout << g << ' ' << h << ' ' << i << '\n';
                cout << '\n';
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
