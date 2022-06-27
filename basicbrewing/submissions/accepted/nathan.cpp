#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ll n, p, r = 0, ra = 0;
  double pd;
  cin >> n >> pd;
  p = round(pd * 100000);
  pair<ll, ll> ms[n];
  vector<ll> idx[2];
  for (ll i = 0; i < n; ++i) {
    cin >> ms[i].second >> pd;
    ms[i].second *= 100000;
    ms[i].first = round(pd * 100000);
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
      if (ms[i].first == p) {
				if (p != r / ra) ra = 0;
			} else ra -= (r - ra * p) / (ms[i].first - p);
      sol = true;
			++i;
      break;
    }
    ++i;
  }
  for (; i < n; ++i) if (ms[i].first == p) ra += ms[i].second, r += ms[i].second * ms[i].first;
  if (sol || ra != 0 && r / ra == p) cout << fixed << setprecision(4) << ra / 100000.0 << endl;
  else cout << 0 << endl;
  return 0;
}
