#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <cmath>
#include <stdio.h>
#define X first
#define Y second

#define _ << " " <<
#define debug(x) #x << " = " << x

#define ll long long
#define ull unsigned long long
#define all(v) v.begin(), v.end()
#define sz(x) (int)x.size()

using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;

const ll mod = 1e9+7;
ll mul(ll a, ll b) {
return (a * b) % mod;
}

ll add(ll a, ll b) {
    ll r = (a + b) % mod;
    if (r < 0) r += mod;
    return r;
}

ll fastpow_mod(ll base, ll exp) {
    if (exp == 1) return base;

    ll t = fastpow_mod(base, exp >> 1);
    t = mul(t, t);

    if (exp & 1) return mul(t, base);
    else return t;
}

ll fastpow(ll base, ll exp) {
    if (exp == 1) return base;
    ll t = fastpow(base, exp >> 1);
    t = t * t;

    if (exp & 1) return t * base;
    else return t;
}

ll invert(ll x) {
    return fastpow_mod(x, mod - 2);
}

struct segment {
    ll from_left;
    ll from_right;
    int len;
};


const int maxn = 2e5+100;
ll pw[maxn];
segment merge(const segment& l, const segment& r)
{
    return {
        .from_left = add(mul(l.from_left, pw[r.len]), r.from_left),
        .from_right = add(l.from_right, mul(r.from_right, pw[l.len])),
        .len = l.len + r.len,
    };
}

segment seg[maxn * 4];
void build(int c = 1, int l = 0, int r = maxn)
{
    seg[c].from_right = 0;
    seg[c].from_left = 0;
    seg[c].len = r - l;

    if (l != r - 1) build(c*2, l, (l+r)/2);
    if (l != r - 1) build(c*2+1, (l+r)/2, r);
}

void add(int pos, ll val, int c = 1, int l = 0, int r = maxn)
{
    if (l == r - 1) {
        seg[c].from_left = add(seg[c].from_left, val);
        seg[c].from_right = add(seg[c].from_right, val);
        return;
    }

    int m = (l + r) / 2;
    if (pos < m) {
        add(pos, val, c * 2, l, m);
    } else {
        add(pos, val, c * 2 + 1, m, r);
    }

    seg[c] = merge(seg[2*c], seg[2*c+1]);
}

segment query(int ql, int qr, int c = 1, int l = 0, int r = maxn)
{
    if (ql <= l && r <= qr) {
       // std::cout << "take" _ debug(l) _ debug(r) _ debug(seg[c].from_left) _ debug(seg[c].len) << std::endl;
        return seg[c];
    }

    segment left = {0, 0, 0};
    segment right = {0, 0, 0};
    int m = (l + r) / 2;
    if (ql < m) left = query(ql, qr, c * 2, l, m);
    if (qr > m) right = query(ql, qr, c * 2 + 1, m, r);
   // std::cout << debug(ql) _ debug(qr) _ debug(l) _ debug(r) _ debug(left.from_left) _ debug(right.from_left) _ debug(left.len) _ debug(right.len) << std::endl;
    return merge(left, right);
}

int main()
{
    std::ios::sync_with_stdio(false);

    int n, q;
    std::string sp;
    std::cin >> n >> q >> sp;

    sp = sp.substr(2);

    ll exp = fastpow_mod(10, sz(sp));
    ll p = mul(exp - std::atoi(sp.c_str()), invert(exp));
    pw[0] = 1;
    for(int i = 1; i < maxn; i++) {
        pw[i] = mul(pw[i - 1], p);
    }
    build();

    for (int i = 0; i < q; i++) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd != "?") {
            int b, x;
            std::cin >> b >> x;
            add(x-1, b * (cmd == "+" ? 1 : -1));
        } else {
            int x;
            std::cin >> x;
            --x;

            auto le = query(0, x + 1);
            auto ri = query(x + 1, n);
    //        std::cout << debug(le.from_left) _ debug(ri.from_right) << std::endl;
            std::cout << add(le.from_left, mul(pw[1], ri.from_right)) << std::endl;
        }
    }

    return 0;
}
