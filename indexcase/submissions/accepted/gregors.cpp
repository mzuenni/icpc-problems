#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
	int n,m; cin >> n >> m;
	int a[m][m][m];
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			for (int k = 0; k < m; ++k) {
				cin >> a[i][j][k];
				a[i][j][k]--;
			}
		}
	}
	vector<int> s(n);
	for (int i = 0; i < n; ++i) {
		cin >> s[i];
		s[i]--;
	} 
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			set<pair<int,int>> valid;
			set<pair<int,int>> v;
			valid.insert({i,j});
			for (int k = 1; k <= n; ++k) {
				for (auto &[x,y] : valid) {
					for (int z = 0; z < m; ++z) {
						if (a[x][y][z] == s[k%n]) {
							v.insert({y,z});
						}
					}
				}
				swap(valid,v);
				v.clear();
			}
			if (valid.count({i,j})) {
				cout << "yes" << endl;
				return 0;
			}
		}
	}
	cout << "no" << endl;
}
