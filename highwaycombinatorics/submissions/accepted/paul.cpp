#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 85, MOD = 1e9 + 7;
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

unordered_set<i64> values;
void gen_partitions(int rem, int amax, i64 x) {
	values.insert(x);
	for (int a = 2; a <= amax && a < rem; a++) {
		gen_partitions(rem-a-1, a, x*fib[a] % MOD);
	}
}

vector<i64> fail = {-1};
vector<i64> reconstruct(i64 y, int rem = N, int amax = N, i64 x = 1) {
	if (x == y) return {};
	for (int a = 2; a <= amax && a < rem; a++) {
		auto v = reconstruct(y, rem-a-1, a, x*fib[a] % MOD);
		if (v != fail) { v.push_back(a); return v; }
	}
	return fail;
}

int main() {
	fib[0] = fib[1] = 1;
	for (int n = 2; n < N; n++) {
		fib[n] = (fib[n-1] + fib[n-2]) % MOD;
	}
	gen_partitions(N, N, 1);
	cerr << values.size() << '\n';

	i64 x; cin >> x;

	if (x == 0) {
		cout << ".##" << '\n' << "##." << '\n';
	} else {
		for (i64 y: values) {
			i64 z = x * inv_mod(y) % MOD;
			if (values.count(z)) {
				string res = "#";
				for (int k: reconstruct(y)) {
					res += string(k, '.') + "#";
				}
				for (int k: reconstruct(z)) {
					res += string(k, '.') + "#";
				}
				cout << res << '\n' << res << '\n';
				break;
			}
		}
	}
}
