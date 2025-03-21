#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> lim(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> lim[i];
    }
    lim[n] = INT_MAX;

    vector<int> next(n);
    stack<int> s;
    s.push(n);
    for (int i = n - 1; i >= 0; i--) {
        while (lim[i] >= lim[s.top()]) {
            s.pop();
        }
        next[i] = s.top();
        s.push(i);
    }

    vector<int> cur(n);
    vector<int> root(n + 1);
    iota(root.begin(), root.end(), 0);
    function<int(int)> get_root = [&](int x) {
        if (x == root[x]) {
            return x;
        }
        return root[x] = get_root(root[x]);
    };

    while (q--) {
        char t;
        int i;
        cin >> t >> i;
        i--;
        if (t == '+') {
            int x;
            cin >> x;
            while (x > 0 && i < n) {
                int add = min(x, lim[i] - cur[i]);
                x -= add;
                cur[i] += add;

                if (cur[i] == lim[i]) {
                    root[i] = get_root(next[i]);
                    i = root[i];
                } else {
                    break;
                }
            }
        } else {
            cout << cur[i] << '\n';
        }
    }
    return 0;
}
