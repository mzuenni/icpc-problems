//
// Created by niko on 5/4/25.
//

#include <bits/stdc++.h>

using namespace std;

int main() {

  long long l, r; cin >> l >> r;
  if (max(l, r) < 1000) {
    std::set<pair<int, int>> s;
    vector<int> a(10 * (l + r));
    for (int i = 0; i < 10; i++) {
      iota(a.begin() + i * (l+r), a.begin() + (i + 1) * (l + r), 0);
    }
    auto b = a;
    rotate(b.begin(), b.begin() + l, b.end());
    for (int i = 0; i < 8 * (l + r); i++) {
      auto u = a[i];
      auto v = b[i];
      if (u < v) swap(u, v);
      s.emplace(u,v);
       u = a[i+ 1];
       v = b[i];
      if (u < v) swap(u, v);
      s.emplace(u,v);
    }
    cout << s.size() << '\n';
    return 0;
  }


  if (l  == r + 2) {
    cout << 3 * l - 3 << '\n';
  } else if (l - 2 >= r || l + 2 <= r || r == l + 1) {
    cout << 2 * (l + r) << '\n';
  } else if (l == r + 1) {
    cout << 2 * r + 1 << '\n';
  } else {
    cout << 3 * l << '\n';
  }

  return 0;
}