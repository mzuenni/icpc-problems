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
	srand(x);
	for (auto [y,i]: v) {
		i64 z = x * inv_mod(y) % MOD;
		int j = lower_bound(begin(v), end(v), make_pair(z, 0)) - begin(v);
		if (j < N && v[j].first == z) {
			vector<int> blocks;
			for (int k: {i, v[j].second}) {
				for (; k > 0; k = prv[k]) {
					blocks.push_back(lst[k]-1);
				}
			}
			if (blocks.empty()) blocks = {1};

			vector<int> walls(int(blocks.size()) - 1, 1);
			while (true) {
				int width = accumulate(begin(blocks), end(blocks), accumulate(begin(walls), end(walls), 0));
				assert(width <= 200);
				if (width == 200) break;
				if (rand() % 2 || walls.empty()) {
					int k = rand() % 2;
					if (width+k+1 > 200) continue;
					blocks.push_back(k);
					walls.push_back(1);
				} else {
					int k = 1 + rand() % 9;
					if (width+k > 200) continue;
					walls[rand() % walls.size()] += k;
				}
			}

			random_shuffle(begin(blocks), end(blocks));
			random_shuffle(begin(walls), end(walls));

			string a, b;
			for (int i = 0; i < int(blocks.size()); i++) {
				int k = blocks[i];
				a += string(k, '.');
				b += string(k, '.');
				if (i == int(walls.size())) break;
				bool first = true;
				for (k = walls[i]; k > 0; ) {
					vector<pair<string,string>> options;
					options.emplace_back("#", "#");
					if (k >= 2) {
						options.emplace_back("##", "..");
						options.emplace_back("..", "##");
					}
					if (k >= 3 && !first) {
						options.emplace_back(".##", "...");
						options.emplace_back(".##", "...");
						options.emplace_back("...", ".##");
						options.emplace_back("...", ".##");
					}
					auto [c,d] = options[rand() % options.size()];
					a += c, b += d,	k -= c.size(), first = false;
				}
			}
			cout << a << '\n' << b << '\n';
			return 0;
		}
	}

	string a(200, '.'), b(200, '.');
	for (int i = 0; i < 100; i++) {
		if (rand() % 4 == 0) {
			int x = rand() % 200;
			if (a[x] == '.' && b[x] == '.') {
				a[x] = b[x] = '#';
			}
		} else {
			if (rand() % 2) swap(a, b);
			int x = rand() % 199;
			if (a[x] == '.' && a[x+1] == '.') {
				a[x] = a[x+1] = '#';
			}
		}
	}
	cout << a << '\n' << b << '\n';
}
