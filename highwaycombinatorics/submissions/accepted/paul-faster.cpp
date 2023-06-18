#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 654321, M = 99, MOD = 1e9 + 7;
i64 val[N], len[N], lst[N], prv[N], fib[M];

i64 inv_mod(i64 x) {
	i64 res = 1;
	for (int n = MOD-2; n > 0; n /= 2, x = x*x % MOD) {
		if (n%2) res = res*x % MOD;
	}
	return res;
}

int main() {
	for (int i = 0, a = 0, b = 1; i < M; i++, a = (a+b) % MOD, swap(a,b)) fib[i] = a;
	val[0] = 1, lst[0] = M-1;
	for (int i = 0, j = 1; j < N; i++) {
		for (int k = 3; k <= min(lst[i], M-len[i]); k++) {
			val[j] = val[i]*fib[k] % MOD;
			len[j] = len[i]+k, lst[j] = k, prv[j] = i;
			if (++j == N) break;
		}
	}

	vector<pair<i64,int>> v;
	for (int i = 0; i < N; i++) v.emplace_back(val[i], i);
	sort(begin(v), end(v));

	i64 x; cin >> x;
	for (auto [y,i]: v) {
		i64 z = x * inv_mod(y) % MOD;
		int j = lower_bound(begin(v), end(v), make_pair(z, 0)) - begin(v);
		if (j < N && v[j].first == z) {
			string res = "#";
			for (int k: {i, v[j].second}) {
				for (; k > 0; k = prv[k]) {
					res += string(lst[k]-1, '.') + "#";
				}
			}
			cout << res << '\n' << res << '\n';
			return 0;
		}
	}
	cout << ".##\n##.\n";
}
