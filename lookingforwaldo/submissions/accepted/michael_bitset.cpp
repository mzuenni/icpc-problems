#include <bits/stdc++.h>
using namespace std;
 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
 
using ll = long long;
using ld = long double;

constexpr int inf = 0x3FFFFFFF;
constexpr ll bits = 64;
constexpr ll mul = 5;

struct myBitset {
	vector<unsigned long long> data;
	myBitset(ll n = 0) : data((n+bits-1)/bits) {}
	bool operator[](size_t i) const {
		return (data[i / bits] & (1ull << (i % bits))) != 0;
	}
	void set(size_t i) {
		data[i / bits] |= 1ull << (i % bits);
	}
	void operator|=(const myBitset& o) {
		for (size_t i = 0; i < data.size(); i++) data[i] |= o.data[i];
	}
};

int solve(int h, int w, vector<myBitset>& in) {
	vector<myBitset> state = in;
	in.push_back(myBitset(w));
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
						if (state[row][r*mul+b]) count[b]++;
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
						if (state[row][l*mul+b]) count[b]--;
					}
					l++;
				}
			}
			state[row] |= in[row + height];
		}
	}
	if (res == inf) res = -1;
	return res;
}

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
	vector<myBitset> in;
	int res;
	if (h < w) {
		in.assign(h, myBitset(mul*w));
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				char c;
				cin >> c;
				int tmp = val[c - 'A'];
				if (tmp >= 0) in[i].set(j*mul+tmp);
			}
		}
		res = solve(h, w, in);
	} else {
		in.assign(w, myBitset(mul*h));
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				char c;
				cin >> c;
				int tmp = val[c - 'A'];
				if (tmp >= 0) in[j].set(i*mul+tmp);
			}
		}
		res = solve(w, h, in);
	}
	if (res < 0) cout << "impossible" << endl;
	else cout << res << endl;
}
