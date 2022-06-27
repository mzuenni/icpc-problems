#include <bits/stdc++.h>
using namespace std;
 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
 
using ll = long long;
using ld = long double;

constexpr int inf = 0x3FFFFFFF;

int solve(int h, int w, vector<vector<uint8_t>>& in) {
	vector<vector<uint8_t>> state = in;
	in.push_back(vector<uint8_t>(w));
	int res = inf;
	for (int height = 1; height <= h; height++) {
		for (int row = 0; row + height <= h; row++) {
			int l = 0;
			int r = 0;
			vector<int> count(5);
			while (r < w) {
				while (r < w && (count[0] == 0 ||
								 count[1] == 0 ||
								 count[2] == 0 ||
								 count[3] == 0 ||
								 count[4] == 0)) {
					for (int b = 0; b < 5; b++) {
						count[b] += (state[row][r] >> b) & 1;
					}
					r++;
				}
				while (count[0] > 0 &&
					   count[1] > 0 &&
					   count[2] > 0 &&
					   count[3] > 0 &&
					   count[4] > 0) {
					res = min(res, height * (r - l));
					for (int b = 0; b < 5; b++) {
						count[b] -= (state[row][l] >> b) & 1;
					}
					l++;
				}
			}
			for (int i = 0; i < w; i++) {
				state[row][i] |= in[row + height][i];
			}
		}
	}
	if (res == inf) res = -1;
	return res;
}

vector<vector<uint8_t>> transpose(vector<vector<uint8_t>>& in) {
	vector<vector<uint8_t>> res(sz(in[0]), vector<uint8_t>(sz(in)));
	for (int i = 0; i < sz(in); i++) {
		for (int j = 0; j < sz(in[i]); j++) {
			res[j][i] = in[i][j];
		}
	}
	return res;
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
	cin >> h >> w;
	vector<vector<uint8_t>> in(h, vector<uint8_t>(w));
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			char c;
			cin >> c;
			in[i][j] = val[c - 'A'];
		}
	}
	if (h > w) {
		swap(h, w);
		in = transpose(in);
	}
	int res = solve(h, w, in);
	if (res < 0) cout << "impossible" << endl;
	else cout << res << endl;
}
