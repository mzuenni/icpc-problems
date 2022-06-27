#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ll n, p, r = 0, ra = 0;
  double pd;
  cin >> n >> pd;
  // Why do I suddenly have to multiply everything with 10 compared to my other submissions?
  p = round(pd * 1000000);
  pair<ll, ll> ms[n];
  vector<ll> idx[2];
  for (ll i = 0; i < n; ++i) {
    cin >> ms[i].second >> pd;
    ms[i].second *= 1000000;
    ms[i].first = round(pd * 1000000);
    r += ms[i].second * ms[i].first;
    ra += ms[i].second;
  }
  r /= ra;
  sort(ms, ms + n);
  if (r < p) reverse(ms, ms + n);
  r = ra = 0;
  ll i = 0;
  bool sol = false;
  while (i < n && (ra == 0 || r / ra != p)) {
    bool old = ra == 0 ? false : r / ra < p;
    ra += ms[i].second;
    r += ms[i].second * ms[i].first;
    if (i > 0 && (r / ra < p) != old) {
      while (ms[i].second > 0 && (ra == 0 || r / ra != p)) --ra, r -= ms[i].first, --ms[i].second;
      ++i;
      break;
    }
    ++i;
  }
  for (; i < n; ++i) if (ms[i].first == p) ra += ms[i].second, r += ms[i].second * ms[i].first;
  if (sol || ra != 0 && r / ra == p) cout << fixed << setprecision(4) << ra / 1000000.0 << endl;
  else cout << 0 << endl;
  return 0;
}

