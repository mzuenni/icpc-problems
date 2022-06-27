#include <climits>
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

using ll = long long;
#define sz(a) ll((a).size())

constexpr ll MAXN = 101101;

const string k = "hdcs";
ll idx[256];

string s;

ll mem[MAXN][4][1u<<4];

ll go(ll i, uint32_t last, uint32_t mask) {
	assert(last < 4 && mask < (1u<<4));
	if (i < 0) return 0;

	if (i == sz(s)) {
		ll res = LLONG_MAX;
		for (ll l = 0; l < 4; l++)
			res = min(res, go(i-1, l, (1<<l)));
		return res;
	}
	ll& res = mem[i][last][mask];
	if (res != -1) return res;
	res = LLONG_MAX;

	const ll j = idx[s[i]];

	if (last == j)
		res = min(res, go(i-1, last, mask));

	// remove i
	res = min(res, 1 + go(i-1, last, mask));

	// choose s[i]
	if ((mask & (1ll<<j)) == 0) {
		res = min(res, go(i-1, j, (mask | (1u<<j))));
	}

	return res;
}

int main () {
	for (ll i = 0; i < 4; i++) idx[k[i]] = i;

	memset(mem, -1, sizeof(mem));

	cin >> s;
	cout << go(sz(s), 0, 0) << endl;

	return 0;
}
