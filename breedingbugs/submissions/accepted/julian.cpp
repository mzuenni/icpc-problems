#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<bool> get_primes(ll n)
{
    ++n;
    vector<bool> is_prime(n, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i < n; ++i) {
        if (is_prime[i]) {
            for (ll j = 2 * i; j < n; j += i) is_prime[j] = false;
        }
    }
    return is_prime;
}


bool find_match(int i, const vector<vector<int>>& adj, vector<int>& mr, vector<int>& mc, vector<bool>& seen) {
    for (int j: adj[i]) {
        if (!seen[j]) {
            seen[j] = true;
            if (mc[j] < 0 || find_match(mc[j], adj, mr, mc, seen)) {
                mr[i] = j;
                mc[j] = i;
                return true;
            }
        }
    }
    return false;
}

int max_bipartite_matching(int n, int m, const vector<vector<int>>& adj) {
    vector<int> mr(n, -1);
    vector<int> mc(m, -1);
    int count = 0;
    vector<bool> seen;
    for (int i = 0; i < n; i++) {
        seen.assign(m, false);
        if (find_match(i, adj, mr, mc, seen)) ++count;
    }
    return count;
}


int main()
{
    int n;
    cin >> n;
    vector<ll> p(n);
    ll max_value = 0;
    for (auto& i: p) {
        cin >> i;
        max_value = max(max_value, i);
    }

    sort(p.begin(), p.end(), std::greater<int>{});
    while (n >= 2 && p[n - 2] == 1) {
        p.pop_back();
        --n;
    }
    reverse(p.begin(), p.end());

    vector<ll> e, o;
    for (int i: p) {
        if (i % 2) o.push_back(i);
        else e.push_back(i);
    }

    auto is_prime = get_primes(2 * max_value);
    vector<vector<int>> adj(o.size());
    for (int i = 0; i < o.size(); ++i) {
        for (int j = 0; j < e.size(); ++j) {
            if (is_prime[o[i] + e[j]]) {
                adj[i].push_back(j);
            }
        }
    }

    cout << n - max_bipartite_matching(o.size(), e.size(), adj) << "\n";
}
