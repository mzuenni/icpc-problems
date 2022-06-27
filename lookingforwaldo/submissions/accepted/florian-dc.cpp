// O(nlogn) divide & conquer
#include <bits/stdc++.h>

using namespace std;

struct {
	vector<vector<int>> d[2][5];
	vector<vector<char>> g;

	void prep() {
		int h = g.size(), w = g[0].size();
		char waldo[] = "WALDO";
		for (int k = 0; k < 5; k++) {
			auto &l = d[0][k], &r = d[1][k];
			l.resize(h, vector<int>(w));
			r.resize(h, vector<int>(w));
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					if (g[i][j] != waldo[k])
						l[i][j] = j == 0 ? -1 : l[i][j-1];
					if (l[i][j] != -1)
						l[i][j]++;
				}
				for (int j = w-1; j >= 0; j--) {
					if (g[i][j] != waldo[k])
						r[i][j] = j == w-1 ? -1 : r[i][j+1];
					if (r[i][j] != -1)
						r[i][j]++;
				}
			}
		}
	}
} s[2]; // original + transpose

int min2(int a, int b) {
	if (a == -1)
		return b;
	if (b == -1)
		return a;
	return min(a, b);
}

int solve(int i1, int j1, int i2, int j2, bool trans)
{
	if ((i2 - i1) * (j2 - j1) < 5)
		return -1;
	if (i2 - i1 > j2 - j1)
		return solve(j1, i1, j2, i2, !trans);
	int m = (j1 + j2)/2;
	int ans = min2(solve(i1, j1, i2, m, trans), solve(i1, m, i2, j2, trans));
	auto& a = s[trans];
	for (int t = i1; t < i2; t++) {
		int best[2][5];
		for (int i = 0; i < 5; i++)
			best[0][i] = best[1][i] = -1;
		for (int b = t; b < i2; b++) {
			for (int i = 0; i < 5; i++) {
				best[0][i] = min2(best[0][i], a.d[0][i][b][m-1]);
				best[1][i] = min2(best[1][i], a.d[1][i][b][m]);
			}
			for (int hi_l = 0; hi_l < 5; hi_l++) {
				int wl = best[0][hi_l], wr = 0;
				if (wl == -1)
					continue;
				bool valid = true;
				for (int i = 0; i < 5; i++)
					if (best[0][i] == - 1 || best[0][i] > wl) {
						valid &= best[1][i] != -1;
						wr = max(wr, best[1][i]);
					}
				if (valid)
					ans = min2(ans, (b - t + 1)*(wl + wr));
			}
		}
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int h, w;
	cin >> h >> w;
	s[0].g.resize(h);
	for (auto& r : s[0].g) {
		string s;
		cin >> s;
		r = { s.begin(), s.end() };
	}
	s[1].g.resize(w, vector<char>(h));
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			s[1].g[j][i] = s[0].g[i][j];
	s[0].prep();
	s[1].prep();
	int res = solve(0, 0, h, w, false);
	if (res < 0) cout << "impossible" << endl;
	else cout << res << endl;
	return 0;
}
