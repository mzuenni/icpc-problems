#include <bits/stdc++.h>
using namespace std;

const int BLOCK_SIZE = 700;
const int RESET_RATE = 5000;

int main() {
	int n, m, q;
	cin >> n >> m >> q;

	list<pair<int,int>> a;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		a.emplace_back(x, 1);
	}

	vector<int> pos;
	vector<list<pair<int,int>>::iterator> its;

	auto reset = [&]() {
		pos.clear(), its.clear();
		int j = 0, sum = 0;
		for (auto it = begin(a); it != end(a); j++, it++) {
			if (j % BLOCK_SIZE == 0) {
				pos.push_back(sum);
				its.push_back(it);
			}
			sum += it->second;			
		}
	};

	reset();
	while (q--) {
		if (q % RESET_RATE == 0) reset();

		int i, x;
		cin >> i >> x;

		int j = upper_bound(begin(pos), end(pos), i) - begin(pos) - 1;
		int s = j >= 0 ? i-pos[j] : i;
		auto it = j >= 0 ? its[j] : begin(a);
		while (s > 0 && it->second <= s) {
			s -= (it++)->second;
		}

		if (s == 0) {
			it = a.emplace(it, x, 1);
		} else {
			auto [y,k] = *it;
			(it++)->second = s;
			it = a.emplace(it, y, k-s);
			it = a.emplace(it, x, 1);
		}
		
		int add = 1, l = i, r = i;
		while (it != end(a)) {
			int kl = 0, kr = 0, y = it->first;
			list<pair<int,int>>::iterator lit = it, rit = it;
			while (lit != begin(a) && prev(lit)->first == y) kl += (--lit)->second;
			while (rit != end(a) && rit->first == y) kr += (rit++)->second;
			it = a.erase(lit, rit);
			l -= kl, r += kr;
			if (kl+kr < m) {
				a.emplace(it, y, kl+kr);
				break;
			}
			add -= kl+kr;
		}

		int jl = lower_bound(begin(pos), end(pos), l) - begin(pos);
		int jr = lower_bound(begin(pos), end(pos), r) - begin(pos);
		if (jl < jr) {
			pos.erase(begin(pos)+jl, begin(pos)+jr);
			its.erase(begin(its)+jl, begin(its)+jr);
		}

		j = lower_bound(begin(pos), end(pos), i) - begin(pos);
		for (; j < ssize(pos); j++) pos[j] += add;
		
		cout << (n += add) << '\n';
	}
}
