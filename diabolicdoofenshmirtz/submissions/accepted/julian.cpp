#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ll end = 0, t = 1;
    do {
        t <<= 1;
        cout << "? " << t - 1 << "\n";
        cin >> end;
    } while (end == t - 1);
    cout << "! " << t - 1 - end << "\n";
}
