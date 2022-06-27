#include <climits>
#include <iostream>
#include <cassert>
#include <cstring>
#include <array>

using namespace std;

using ll = long long;
#define sz(a) ll((a).size())

constexpr ll MAXN = 101101;

const string k = "hdcs";
ll idx[256];

int main () {
	for (ll i = 0; i < 4; i++) idx[k[i]] = i;

	string s;
	cin >> s;

	using DP = array<array<ll,1<<4>, 4>;

	DP mem;
	for (auto& a : mem)
		a.fill(0ll);

	for (const char c : s) {
		const ll j = idx[c];
		DP mem2;

		for (ll last = 0; last < 4; last++)
			for (ll mask = 0; mask < (1<<4); mask++) {
				ll& res = mem2[last][mask];
				res = LLONG_MAX;

				if (last == j)
					res = min(res, mem[last][mask]);

				// remove i
				res = min(res, 1 + mem[last][mask]);

				// choose s[i]
				if ((mask & (1ll<<j)) == 0)
					res = min(res, mem[j][mask | (1u<<j)]);
			}
		mem = move(mem2);
	}

	ll res = LLONG_MAX;
	for (ll i = 0; i < 4; i++)
		res = min(res, mem[i][1<<i]);
	cout << res << endl;

	return 0;
}
