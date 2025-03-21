#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> cap(n), lvl(n);
    for (int &x: cap) cin >> x;

    set<int> todo;
    for (int i = 0; i < n; i++) {
        todo.insert(i);
    }

    while (q--) {
        char t;
        int k;
        cin >> t >> k;
        k--;
        if (t == '+') {
            int x; cin >> x;
            for (auto it = todo.lower_bound(k); it != end(todo); ) {
                k = *it;
                int y = min(x, cap[k]-lvl[k]);
                x -= y, lvl[k] += y;
                if (lvl[k] == cap[k]) it = todo.erase(it);
                if (x == 0) break;
            }
        } else {
            cout << lvl[k] << endl;
        }
    }
}
