#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <cassert>
#include <random>
#include <chrono>

using namespace std;

using ll = int;
using pll = pair<ll,ll>;

#define all(a) (a).begin(),(a).end()

void quit(bool res) {
	cout << ("impossible\n" + 2*res);
	exit(0);
}

int main() {
	const auto start = chrono::system_clock::now();
	ll w, h;
	cin >> w >> h;
	vector<ll> in(w);
	for (ll&y:in) cin >> y, y = h - y;
	if (*min_element(all(in)) < 0) quit(false);
	if (accumulate(all(in), 0) % 2 == 1)
		quit(false);

	{
		ll s = accumulate(all(in), 0);
		double x = 3e7 / s;
		for (ll& y : in) {
			ll steps = max<ll>(10, y * x);
			if (y > steps) {
				assert(y % 2 == (steps + (y - steps) % 2) % 2);
				y = steps + (y - steps) % 2;
			}
		}
	}

	priority_queue<pll> pq;
	for (ll i = 0; i < w; i++)
		if (in[i] > 0)
			pq.emplace(in[i], -i);
	while (not pq.empty()) {
		if (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start).count()/1e3 > 0.95) {
			   mt19937 gen(random_device{}());
			   uniform_int_distribution<> distrib(0, 1);
			   quit(distrib(gen));
		}

		auto [hh,i] = pq.top(); pq.pop();
		i = -i;
		if (in[i] != hh) continue;
		ll num = 1;
		while (i + num < w and in[i] == in[i+num]) num++;
		ll b = 0;
		if (i > 0) b = max(b, in[i-1]);
		if (i + num < w) b = max(b, in[i + num]);
		if (num % 2 == 0 or (in[i] - b) % 2 == 0)
			for (ll j = i; j < i + num; j++)
				in[j] = b;
		else {
			if (b - 1 < 0) quit(false);
			for (ll j = i; j < i + num; j++)
				in[j] = b - 1;
		}
		ll j = i;
		if (in[j] > 0) pq.emplace(in[j], -j);
		j = i + num - 1;
		if (num > 1 and j < w and in[j] > 0) pq.emplace(in[j], -j);
	}
	quit(true);

	return 0;
}
