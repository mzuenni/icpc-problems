#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> cap(n), lvl(n+1);
    for (int &x: cap) cin >> x;
    cap.push_back(INT_MAX);

    vector<int> par(n+1), stk = {n};
    for (int i = n-1; i >= 0; i--) {
        while (cap[stk.back()] <= cap[i]) stk.pop_back();
        par[i] = stk.back();
        stk.push_back(i);
    }

    while (q--) {
        char t;
        int k;
        cin >> t >> k;
        k--;
        if (t == '+') {
            int x; cin >> x;
            while (k < n && x > 0) {
                int y = min(x, cap[k]-lvl[k]);
                x -= y, lvl[k] += y;
                int nk = k;
                while (lvl[nk] == cap[nk]) nk = par[nk];
                while (lvl[k] == cap[k]) {
                    tie(k, par[k]) = make_pair(par[k], nk);
                }
            }
        } else {
            cout << lvl[k] << endl;
        }
    }
}
