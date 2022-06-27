#include "validate.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

constexpr Integer N = 20000007;
bitset<N / 2> isNotPrime;

bool isPrime(Integer x) {
	if (x < 2 || x % 2 == 0) return x == 2;
	else return !isNotPrime[x / 2];
}

void primeSieve() {
	// i * i < N is enough for isPrime
	for (Integer i = 3; i < N; i += 2) {
		if (!isNotPrime[i / 2]) {
			for (Integer j = i * i; j < N; j+= 2 * i) {
				isNotPrime[j / 2] = 1;
			}
		}
	}
}

int main(int argc, char **argv) {
	using namespace Generator;
	Generator::init(argc, argv);
	
	primeSieve();

	Integer n = arguments["--n"].asInteger();
	Integer noise = arguments["--noise"].asInteger(0);

	vector<vector<Integer>> paths;
	auto clean = [&](){
		for (Integer j = 0; j < sz(paths); j++) {
			if (sz(paths[j]) % 2 == 0) paths[j].pop_back();
			if (sz(paths[j]) == 1) {
				swap(paths[j], paths.back());
				paths.pop_back();
				j--;
			}
		}
	};

	for (Integer i = 0; i < 100000; i++) {
		Integer x = Random::integer(1, 10000000);
		vector<Integer> ns;
		for (Integer j = 0; j < sz(paths); j++) {
			for (Integer y : paths[j]) {
				if (isPrime(x+y)) {
					ns.push_back(j);
				}
			}
		}
		if (ns.empty()) paths.push_back({x});
		else if (sz(ns) == 1) paths[ns[0]].push_back(x);
		
		if (Random::integer(0, 100) == 0) clean();
	}
	clean();
	sort(all(paths), [](const vector<Integer>& a, const vector<Integer>& b){
		return sz(a) > sz(b);
	});

	Integer x = 0;
	for (auto p : paths) x += sz(p);
	while (x - sz(paths.back()) > n) {
		x -= sz(paths.back());
		paths.pop_back();
	}

	vector<Integer> out;
	for (auto p : paths) {
		for (auto x : p) {
			if (sz(out) < n) out.push_back(x);
		}
	}
	for (Integer i = 0; i < noise; i++) {
		out[sz(out) - i - 1] = Random::integer(1, 10000000);
	}
	Random::shuffle(all(out));

	testOut << sz(out) << endl;
	testOut << join(all(out)) << endl;
}
