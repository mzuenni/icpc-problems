#include <bits/stdc++.h>
using namespace std;

struct matching {
	int L, R;
	vector<vector<int>> adj;
	vector<int> matchR, mark;

	matching(int L, int R): L(L), R(R), adj(L), matchR(R,-1) { }

	bool dfs(int i) {
		if (i == -1) return true;
		if (mark[i]) return false;
		mark[i] = true;
		for (int j: adj[i]) if (dfs(matchR[j])) {
			matchR[j] = i;
			return true;
		}
		return false;
	}
	
	int max_match() {
		int res = 0;
		for (int i = 0; i < L; i++) {
			mark.assign(L,false);
			if (dfs(i)) res++;
		}
		return res;
	}
};

int main() {
	int m = 2e7 + 10;
	vector<bool> isp(m, true);
	isp[0] = isp[1] = false;
	for (int i = 2; i*i < m; i++) if (isp[i]) {
		for (int j = i*i; j < m; j += i) isp[j] = false;
	}

	int n; cin >> n;

	bool have_one = false;
	vector<int> odd, even;
	while (n--) {
		int x; cin >> x;
		if (x%2 == 0) even.push_back(x);
		else if (x != 1 || !have_one) odd.push_back(x);
		if (x == 1) have_one = true;
	}

	int L = size(odd), R = size(even);
	matching M(L,R);
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < R; j++) {
			if (isp[ odd[i]+even[j] ]) {
				M.adj[i].push_back(j);
			}
		}
	}
	cout << L + R - M.max_match() << '\n';
}
