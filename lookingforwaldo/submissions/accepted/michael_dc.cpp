#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll inf = 0xFFFFFFF;
constexpr ll chars = 5;

vector<vector<vector<uint8_t>>> in(2);

ll solveLine(const vector<int>& a, const vector<int>& b) {
	vector<pair<int, int>> line;
	for (int i = 0; i < chars; i++) {
		line.push_back({a[i], i});
		line.push_back({b[i], i});
	}
	sort(all(line));
	int res = inf;
	vector<int> count(chars);
	int active = 0;
	for (int l = 0, r = 0; l < chars; l++) {
		while (r < 2*chars && active < chars) {
			if (count[line[r].second] == 0) active++;
			count[line[r].second]++;
			r++;
		}
		if (active == chars && r > chars) res = min(res, line[r-1].first-line[l].first+1);
		count[line[l].second]--;
		if (count[line[l].second] == 0) active--;
	}
	return res;
}

ll solve(int l, int d, int r, int u, int index) {
	if ((r-l)*(u-d) < chars) return inf;
	if (r-l < u-d) {
		swap(l, d);
		swap(r, u);
		index ^= 1;
	}
	int m = (l+r)/2;
	ll res = min(solve(l, d, m, u, index), 
				 solve(m, d, r, u, index));

	//calculate this on the fly, since we can look at each cell.
	vector<vector<int>> pl(u-d, vector<int>(chars+1, -2*inf));
	vector<vector<int>> pr(u-d, vector<int>(chars+1,  2*inf));
	for (int i = d; i < u; i++) {
		for (int j = 0; j < m; j++)
			pl[i-d][in[index][i][j]] = j;
		for (int j = r-1; j >= m; j--)
			pr[i-d][in[index][i][j]] = j;
	}

	for (int i = d; i < u; i++) {
		auto cl = pl[i-d];
		auto cr = pr[i-d];
		for (int j = i; j < u; j++) {
			for (int k = 0; k < chars; k++) {
				cl[k] = max(cl[k], pl[j-d][k]);
				cr[k] = min(cr[k], pr[j-d][k]);
			}
			res = min(res, solveLine(cl, cr)*(j-i+1));
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<uint8_t> val(26, chars);
	val['W' - 'A'] = 0;
	val['A' - 'A'] = 1;
	val['L' - 'A'] = 2;
	val['D' - 'A'] = 3;
	val['O' - 'A'] = 4;

	int h, w;
	cin >> h >> w;
	in[0].assign(h, vector<uint8_t>(w));
	in[1].assign(w, vector<uint8_t>(h));
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			char c;
			cin >> c;
			in[0][i][j] = in[1][j][i] = val[c - 'A'];
		}
	}
	ll res = solve(0, 0, w, h, 0);
	if (res >= inf) cout << "impossible" << endl;
	else cout << res << endl;
}
