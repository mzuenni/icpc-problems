#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

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
		if (i + 1 < w and in[i] == in[i+1]) {
			in[i]--, in[i+1]--;
			if (in[i] > 0) pq.emplace(in[i], -i), pq.emplace(in[i+1], -(i+1));
		} else {
			if (in[i] == 1) quit(false);
			in[i] -= 2;
			if (in[i] > 0) pq.emplace(in[i], -i);
		}
	}
	quit(true);

	return 0;
}
