#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <cassert>

using namespace std;

using ll = long long;
using pll = pair<ll,ll>;

#define all(a) (a).begin(),(a).end()

void quit(bool res) {
	cout << ("impossible\n" + 2*res);
	exit(0);
}

int main() {
	ll w, h;
	cin >> w >> h;
	vector<ll> in(w);
	for (ll&y:in) cin >> y, y = h - y;
	if (*min_element(all(in)) < 0) quit(false);
	if (accumulate(all(in), 0) % 2 == 1)
		quit(false);

	priority_queue<pll> pq;
	for (ll i = 0; i < w; i++)
		if (in[i] > 0)
			pq.emplace(in[i], -i);
	while (not pq.empty()) {
		auto [hh,i] = pq.top(); pq.pop();
		i = -i;
		if (in[i] != hh) continue;
		ll num = 1;
		while (i + num < w and in[i] == in[i+num]) num++;
		ll b = 0;
		if (i > 0) b = max(b, in[i-1]);
		if (i + num < w) b = max(b, in[i + num]);
		for (ll j = i; j < i + num; j++) {
			if (j + 1 == i + num and num % 2 == 1) {
				in[j] = b - (in[j] - b) % 2;
				if (in[j] < 0)
					quit(false);
			} else {
				in[j] = b;
			}
			if (in[j] > 0) pq.emplace(in[j], -j);
		}
	}
	quit(true);

	return 0;
}
