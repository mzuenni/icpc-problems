#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,link-pipe-args,inline")
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#include <bits/stdc++.h>
using namespace std;

short int mul[40];

string operator*(string a, string b)
{
    signed char n = a.size(), m = b.size(), cnt = n + m;
    memset(mul, 0, sizeof(mul));
    for (signed char i = 0; i < n; i++)
        for (signed char j = 0; j < m; j++) mul[i + j] += (a[i] - '0') * (b[j] - '0');
    for (signed char i = 0; i < cnt; i++)
    {
        mul[i + 1] += mul[i] / 10;
        mul[i] %= 10;
    }
    while (!mul[cnt]) cnt--;
    string res = "";
    for (signed char i = cnt; i >= 0; i--) res += mul[i] + '0';
    return res;
}

string a, b, c, d;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b97f4a7c16 + (h1<<6) + (h1>>2));
    }
};

unordered_map<pair<string, string>, string, pair_hash> s;

void generate(string& a, unordered_map<pair<string, string>, string, pair_hash>& s, string& d)
{
    int n = a.length();
    for (int i = 1; i < (1<<n); i++)
    {
        string b = "", c = "";
        if (a[31 - __builtin_clz(i)] == '0') continue;
        for (int j = 0; j < n; j++)
        {
            if ((i & (1<<j))) b += a[j];
            else c += a[j];
        }
        sort(c.begin(), c.end());
        s[{c, b*d}] = b;
    }
}

void generate_and_find(string& a, unordered_map<pair<string, string>, string, pair_hash>& s, string& d)
{
    int n = a.length();
    for (int i = 1; i < (1<<n); i++)
    {
        string b = "", c = "";
        if (a[31 -__builtin_clz(i)] == '0') continue;
        for (int j = 0; j < n; j++)
        {
            if ((i & (1<<j))) b += a[j];
            else c += a[j];
        }
        sort(c.begin(), c.end());
        if (s.find({c, b*d}) != s.end())
        {
            cout << "possible\n";
            string t = s[{c, b*d}];
            reverse(t.begin(), t.end());
            reverse(b.begin(), b.end());
            cout << t << " " << b << "\n";
            exit(0);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> a >> b >> c >> d;
    // reverse all the numbers beforehand to speed up multiplication
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    reverse(c.begin(), c.end());
    reverse(d.begin(), d.end());
    generate(a, s, d);
    generate_and_find(b, s, c);
    cout << "impossible\n";
}