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
	Integer lim = arguments["--lim"].asInteger();
	Integer range = arguments["--range"].asInteger();

	vector<Integer> integers(lim);
	for (Integer i = 0; i < lim; i++) integers[i] = range - i - 1;
	vector<vector<Integer>> adj(lim);
	for (Integer i = 0; i < lim; i++) {
		for (Integer j = 0; j < i; j++) {
			if (isPrime(integers[i] + integers[j])) {
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
	}

	vector<Integer> deg(lim);
	priority_queue<pair<Integer, Integer>, vector<pair<Integer, Integer>>, less<pair<Integer, Integer>>> todo;
	for (Integer i = 0; i < lim; i++) {
		deg[i] = sz(adj[i]);
		todo.push({deg[i], i});
	}

	Integer cur = lim;
	while (cur > n) {
		Integer d = todo.top().first;
		Integer i = todo.top().second;
		todo.pop();
		if (deg[i] != d) continue;
		deg[i] = -1;
		cur--;
		for (Integer j : adj[i] ) {
			deg[j]--;
			if (deg[j] >= 0) todo.push({deg[j], j});
		}
	}

	vector<Integer> out;
	Integer sum = 0;
	for (Integer i = 0; i < lim; i++) {
		if (deg[i] >= 0) {
			out.push_back(integers[i]);
			sum += deg[i];
		}
	}
	assert(sz(out) == n);

	Random::shuffle(all(out));

	testOut << n << endl;
	testOut << join(all(out)) << endl;
}
