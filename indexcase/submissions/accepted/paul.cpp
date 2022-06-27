#include <bits/stdc++.h>
using namespace std;

int a[10][10][10], b[200];

int main() {
	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < m; k++) {
				cin >> a[i][j][k];
				a[i][j][k]--;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		cin >> b[i];
		b[i]--;
	}

	for (int x = 0; x < m; x++) {
		for (int y = 0; y < m; y++) {
			vector<int> dp(m*m);
			dp[m*x+y] = 1;
			for (int i = 0; i < n; i++) {
				vector<int> ndp(m*m);
				for (int u = 0; u < m; u++) {
					for (int v = 0; v < m; v++) {
						if (!dp[m*u+v]) continue;
						for (int w = 0; w < m; w++) {
							if (a[u][v][w] == b[(i+n-1)%n]) ndp[m*v+w] = 1;
						}
					}
				}
				dp = ndp;
			}
			if (dp[m*x+y]) {
				cout << "YES" << endl;
				return 0;
			}
		}
	}

	cout << "NO" << endl;
}
