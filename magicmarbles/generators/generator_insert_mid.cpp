#include "mz_validate.h"
#include "solution.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (integer_t)(x).size()

constexpr integer_t n = 200000;
constexpr integer_t k = 7;
constexpr integer_t q = 200000;
constexpr integer_t sigma = 8;

vector<integer_t> generateInit() {
	vector<integer_t> res;
	while (sz(res) < n) {
		integer_t l = randomInteger<integer_t>(1, k);
		integer_t x = randomInteger<integer_t>(1, sigma);
		while (!res.empty() && x == res.back()) x = randomInteger<integer_t>(1, sigma);
		for (integer_t i = 0; i < l && sz(res) < n; i++) res.push_back(x);
	}
	return res;	
}

int main(int argc, char **argv) {
	init_gen(argc, argv);
	//jerr	error output stream
	//jans	generator input (cin)

	//jout	testcase output stream
	//use std::mt19937_64 mz_rng
	jout << n << " " << k << " " << q << endl;
	auto m = generateInit();
	jout << outList(all(m)) << endl;
	marbles state(k);
	for (integer_t i = 0; i < n; i++) state.add(i, m[i]);
	bool degenerated = false;
	for (integer_t i = 0; i < q; i++) {
		assert(sz(state) >= 150000ll);
		integer_t p = randomInteger<integer_t>(100000ll, min(150000ll, state.size()));
		integer_t x = randomInteger<integer_t>(1ll, sigma);
		jout << p << " " << x << endl;
		state.add(p, x);
	}
	jerr << sz(state) << endl;
}
