// Has a ~ 1 / 39 chance of using more than 40 queries.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr ll initial_query_cnt = 1;
constexpr ll max_length = 1000ll * 1000 * 1000 * 1000;

mt19937 e;

ll query(ll t)
{
    cout << "? " << t << "\n";
    ll result;
    cin >> result;
    return result;
}

int main()
{
    e.seed(84574241);
    vector<ll> queries(initial_query_cnt);
    for (auto& i: queries) i = uniform_int_distribution<ll>(max_length, 2 * max_length)(e);
    sort(queries.begin(), queries.end());

    ll dist = -1, result;
    for (ll i: queries) {
        cout << "? " << i << "\n";
        cin >> result;
        if (result >= dist) dist = result + 1;
    }

    pair<ll, ll> results = {-1, result};
    ll last_query = queries.back();
    while (results.first < results.second) {
        swap(results.first, results.second);
        last_query += dist;
        cout << "? " << last_query << "\n";
        cin >> results.second;
    }

    cout << "! " << results.first + dist - results.second << "\n";
}
