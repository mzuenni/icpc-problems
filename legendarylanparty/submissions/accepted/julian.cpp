#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<ll, ll>> v(n);
    for (auto& [a, b]: v) cin >> a >> b;
    sort(v.begin(), v.end(), [](auto x, auto y){ return y.first * x.second < x.first * y.second; });
    ll dist = 1, sum = 0;
    for (auto [a, b]: v) {
        sum += a * dist;
        dist += b;
    }
    cout << sum << "\n";
}
