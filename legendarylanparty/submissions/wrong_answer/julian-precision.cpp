#include <algorithm>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<ll, ll>> v(n);
    for (auto& [a, b]: v) cin >> a >> b;

    // The 52 bit precision of double are probably enough to distinguish all relevant fractions, but the 23 bit precision of float are not enough
    sort(v.begin(), v.end(), [](auto x, auto y){ return static_cast<float>(y.first) / y.second < static_cast<float>(x.first) / x.second; });

    ll dist = 1, sum = 0;
    for (auto [a, b]: v) {
        sum += a * dist;
        dist += b;
    }
    cout << sum << "\n";
}
