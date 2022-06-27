// Should take at most 30 queries. Probably still not optimal.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr ll first_query = 2048;

ll query(ll t)
{
    cout << "? " << t << "\n";
    ll result;
    cin >> result;
    return result;
}

int main()
{
    ll end = 0;
    ll t = first_query / 2;
    do {
        t <<= 1;
        end = query(t);
    } while (end == t);

    if (t == first_query && end < first_query / 2) {
        ll first_result = end;
        ll result = end;
        do {
            ++t;
            ++result;
            if (first_query % result == first_result) end = query(t);
        } while (end != 0);
        cout << "! " << result << "\n";
    } else {
        cout << "! " << t - end << "\n";
    }
}
