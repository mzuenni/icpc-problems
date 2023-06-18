#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int MOD = 1e9 + 7;

int exp_mod(i64 a, int k) {
	i64 res = 1;
	for (; k > 0; k /= 2, a = a*a % MOD) {
		if (k%2 > 0) res = res*a % MOD;
	}
	return res;
}

int inv_mod(int a) {
	return exp_mod(a, MOD-2);
}

const int M = 33333, g = 5, x = exp_mod(g, M), y = inv_mod(g);
map<int,int> table;

int dlog(int a) {
	// g^(i*M+j) == a <-> x^i == a * y^j
	for (int j = 0; j < M; j++, a = i64(a)*y % MOD) {
		if (table.count(a)) return (table[a]*M + j) % (MOD-1);
	}
	assert(0);
}

const int K = 95;

int main() {
	srand(123);
	for (int i = 0, z = 1; i < M; i++, z = i64(z)*x % MOD) {
		table[z] = i;
	}

	vector<int> lfib(K);
	for (int k = 0, a = 1, b = 1; k < K; k++, a = (a+b) % MOD, swap(a, b)) {
		lfib[k] = dlog(a);
	}

	unordered_map<int,vector<int>> halves;

	vector<int> part;
	auto rec = [&](const auto &self, int imax, int s, int x) -> void {
		if (halves.count(x)) return;
		if (int(halves.size()) >= 1e6) return;
		halves[x] = part;

		imax = min(imax, K-1-s);
		for (int i = imax; i >= 2; i--) {
			part.push_back(i);
			self(self, i, s+i+1, (x+lfib[i]) % (MOD-1));
			part.pop_back();
		}
	};
	rec(rec, K-1, -1, 0);

	int a; cin >> a;
	if (a == 0) {
		cout << "##.\n.##\n";
		return 0;
	}
	a = dlog(a);

	for (auto [x,_]: halves) {
		int y = (a-x+MOD-1) % (MOD-1);
		if (halves.count(y)) {
			string res = "#";
			for (int z: {x, y}) for (int k: halves[z]) {
				res += string(k, '.') + "#";
			}
			cout << res << '\n' << res << '\n';
			return 0;
		}
	}
}
