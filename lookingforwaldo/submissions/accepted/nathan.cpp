#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll h, w, l, r, cnt[5], res = 0x3f3f3f3f3f3f3f3f;
    cin >> h >> w;
    char x;
    vector<vector<bitset<5>>> c(min(h, w) + 1, vector<bitset<5>>(max(h, w))),
                              d(min(h, w), vector<bitset<5>>(max(h, w)));
    for (ll i = 0; i < h; ++i)
        for (ll j = 0; j < w; ++j) {
            cin >> x;
            ll a = h < w ? i : j, b = h < w ? j : i;
            if (x == 'W') c[a][b] = d[a][b] = 1;
            if (x == 'A') c[a][b] = d[a][b] = 2;
            if (x == 'L') c[a][b] = d[a][b] = 4;
            if (x == 'D') c[a][b] = d[a][b] = 8;
            if (x == 'O') c[a][b] = d[a][b] = 16;
        }
    if (h > w) swap(h, w);
    for (ll he = 1; he <= h; ++he)
        for (ll ro = 0; ro + he <= h; ++ro) {
            l = r = 0;
            memset(cnt, 0, sizeof(cnt));
            while (r < w) {
                while (r < w && !(cnt[0] && cnt[1] && cnt[2] && cnt[3] && cnt[4])) {
                    for (ll i = 0; i < 5; ++i)
                        if (d[ro][r][i]) ++cnt[i];
                    ++r;
                }
                while (cnt[0] && cnt[1] && cnt[2] && cnt[3] && cnt[4]) {
					res = min(res, he * (r - l));
                    for (ll i = 0; i < 5; ++i)
                        if (d[ro][l][i]) --cnt[i];
                    ++l;
                }
            }
            for (ll i = 0; i < w; ++i) d[ro][i] |= c[ro + he][i];
        }
    if (res == 0x3f3f3f3f3f3f3f3f) cout << "impossible" << endl;
    else cout << res << endl;
    return 0;
}

