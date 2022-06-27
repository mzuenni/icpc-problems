#include <bits/stdc++.h>
using namespace std;
 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
 
using ll = long long;
using ld = long double;

constexpr int inf = 0x3FFFFFFF;

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
	cin >> h >> w;
	vector<vector<uint8_t>> in(h, vector<uint8_t>(w));
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			char c;
			cin >> c;
			in[i][j] = val[c - 'A'];
		}
	}
	int res = inf;
	for (int sy = 0; sy < h; sy++) {
		for (int sx = 0; sx < w; sx++) {
			for (int ey = sy+1; ey <= h; ey++) {
				for (int ex = sx+1; ex <= w; ex++) {
					int c = 0;
					for (int y = sy; y < ey; y++) {
						for (int x = sx; x < ex; x++) {
							c |= in[y][x];
						}
					}
					if (c == 0b11111) {
						res = min(res, (ey - sy) * (ex - sx));
					}
				}
			}
		}
	}
	if (res == inf) cout << "impossible" << endl;
	else cout << res << endl;
}
