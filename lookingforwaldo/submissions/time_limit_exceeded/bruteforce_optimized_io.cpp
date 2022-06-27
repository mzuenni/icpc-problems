#include <bits/stdc++.h>
using namespace std;
 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
 
using ll = long long;
using ld = long double;

constexpr int inf = 0x3FFFFFFF;

void fastscan(int& number) {
	int c;
	number = 0;
	c = getchar();
	while (c < '0') c = getchar();
	for (; c >= '0'; c = getchar()) number = number * 10 + c - '0';
}

void fastscanChar(int& c) {
	c = getchar();
	while (c < 'A') c = getchar();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<uint8_t> val(26);
	val['W' - 'A'] = 1;
	val['A' - 'A'] = 2;
	val['L' - 'A'] = 4;
	val['D' - 'A'] = 8;
	val['O' - 'A'] = 16;

	int h, w;
	fastscan(h);
	fastscan(w);
	vector<vector<uint8_t>> in(h, vector<uint8_t>(w));
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int c;
			fastscanChar(c);
			in[i][j] = val[c - 'A'];
		}
	}
	int res = inf;
	for (int sy = 0; sy < h; sy++) {
		for (int sx = 0; sx < w; sx++) {
			vector<ll> c(w + 1);
			for (int y = sy; y < h; y++) {
				for (int x = sx; x < w; x++) {
					c[x + 1] |= c[x] | in[y][x];
					if (c[x + 1] == 0b11111) {
						res = min(res, (y - sy + 1) * (x - sx + 1));
					}
				}
			}
		}
	}
	if (res == inf) cout << "impossible" << endl;
	else cout << res << endl;
}
