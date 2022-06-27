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
	vector<int> val(26, -1);
	val['W' - 'A'] = 0;
	val['A' - 'A'] = 1;
	val['L' - 'A'] = 2;
	val['D' - 'A'] = 3;
	val['O' - 'A'] = 4;

	int h, w;
	cin >> h >> w;
	vector<vector<vector<int>>> in(5, vector<vector<int>>(h+1, vector<int>(w+1)));
	int seen = 0;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			char c;
			cin >> c;
			for (int k = 0; k < 5; k++) in[k][i][j] = in[k][i-1][j]+in[k][i][j-1]-in[k][i-1][j-1];
			if (val[c - 'A'] >= 0) {
				in[val[c - 'A']][i][j]++;
				seen |= 1 << val[c - 'A'];
			}
		}
	}
	if (seen != 0b11111) {
		cout << "impossible" << endl;
		return 0;
	}

	int res = inf;
	for (int sy = 0; sy < h; sy++) {
		for (int sx = 0; sx < w; sx++) {
			for (int ey = sy+1; ey <= h; ey++) {
				for (int ex = sx+1; ex <= w && (ey - sy) * (ex - sx) < res; ex++) {
					int c = 0;
					for (int k = 0; k < 5; k++) {
						int cur = in[k][ey][ex] - in[k][sy][ex] - in[k][ey][sx] + in[k][sy][sx];
						if (cur > 0) c++;
						else break;
					}
					if (c == 5) res = (ey - sy) * (ex - sx);
				}
			}
		}
	}
	cout << res << endl;
}
