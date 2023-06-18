#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 111, MOD = 1e9 + 7;
int fib[N];

i64 exp_mod(i64 a, i64 n) {
	i64 res = 1;
	for (; n > 0; n /= 2) {
		if (n%2) res = res*a % MOD;
		a = a*a % MOD;
	}
	return res;
}

i64 inv_mod(i64 a) {
	return exp_mod(a, MOD-2);
}

i64 dp[N][N];
i64 rec(int n, int a) {
	if (a > n) return 1;
	if (dp[n][a]) return dp[n][a];
	return dp[n][a] = rec(n-a, a) + rec(n, a+1);
}

mt19937_64 gen(987);
vector<int> random_partition() {
	int n = 100, a = 3;
	i64 k = uniform_int_distribution<i64>(0, rec(n, 3))(gen);
	vector<int> part;
	while (n >= a) {
		if (k < rec(n-a, a)) {
			part.push_back(a);
			n -= a;
		} else {
			k -= rec(n-a, a);
			a++;
		}
	}
	return part;
}

int main() {
	fib[0] = fib[1] = 1;
	for (int n = 2; n < N; n++) {
		fib[n] = (fib[n-1] + fib[n-2]) % MOD;
	}

	i64 x; cin >> x;

	if (x == 0) {
		cout << ".##" << '\n' << "##." << '\n';
	} else {
		map<i64, vector<int>> cache;
		while (true) {
			auto part = random_partition();
			i64 y = 1;
			for (int k: part) {
				y = y*fib[k-1] % MOD;
			}
			cache[y] = part;
			i64 z = x * inv_mod(y) % MOD;
			if (cache.count(z)) {
				string res;
				for (int k: part) {
					res += string(k-1, '.') + "#";
				}
				for (int k: cache[z]) {
					res += string(k-1, '.') + "#";
				}
				if (res == "") res = ".";
				cout << res << '\n' << res << '\n';
				cerr << cache.size() << '\n';
				break;
			}
		}
	}
}
