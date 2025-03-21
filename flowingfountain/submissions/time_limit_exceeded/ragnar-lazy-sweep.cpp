#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, q;
	cin >> n >> q;
	vector<long long> c(n + 2, 0);
	for(int i = 1; i <= n; ++i) cin >> c[i];

	vector<int> next(n + 1, n + 1);
	vector<int> tmp;
	for(int i = n; i > 0; --i) {
		while(!tmp.empty() && c[tmp.back()] <= c[i]) {
			tmp.pop_back();
		}
		if(!tmp.empty()) {
			next[i] = tmp.back();
		}
		tmp.push_back(i);
	}

	vector<long long> f(n + 3, 0);
	int update_from = n;
	for(int t = 0; t < q; ++t) {
		char op;
		int i;
		cin >> op >> i;
		if(op == '+') {
			int add;
			cin >> add;
			f[i] += add;
			update_from = min(update_from, i);
		}
		if(op == '?') {
			if(update_from <= i) {
				// Update from update_from to i.
				for(int j = update_from; j <= i; ++j) {
					if(f[j] > c[j]) {
						f[next[j]] += f[j] - c[j];
						f[j] = c[j];
					}
				}
				for(int j = 1; j <= n; ++j) {
				}
			}
			update_from = i + 1;
			cout << f[i] << endl;
		}
	}
}
