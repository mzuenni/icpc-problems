#include <bits/stdc++.h>
using namespace std;

int main() {
	int m, n;
	cin >> m >> n;

	vector<string> a(m);
	for (string &s: a) cin >> s;

	if (m > n) {
		vector<string> b(n, string(m,' '));
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				b[j][i] = a[i][j];
			}
		}
		swap(m,n), swap(a,b);
	}

	int res = m*n+1;
	for (int imin = 0; imin < m; imin++) {
		vector<vector<int>> next(n+1, vector<int>(5,n));
		for (int imax = imin; imax < m; imax++) {
			for (int j = n-1; j >= 0; j--) {
				if (a[imax][j] == 'W') next[j][0] = j;
				if (a[imax][j] == 'A') next[j][1] = j;
				if (a[imax][j] == 'L') next[j][2] = j;
				if (a[imax][j] == 'D') next[j][3] = j;
				if (a[imax][j] == 'O') next[j][4] = j;
				for (int k = 0; k < 5; k++) {
					next[j][k] = min(next[j][k], next[j+1][k]);
				}
			}
			for (int jmin = 0; jmin < n; jmin++) {
				int jmax = *max_element(begin(next[jmin]), end(next[jmin]));
				if (jmax == n) break;
				res = min(res, (imax-imin+1)*(jmax-jmin+1));
			}
		}
	}

	if (res <= m*n) cout << res << endl;
	else cout << "impossible" << endl;
}
