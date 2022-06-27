#include "mz_validate.h"
#include "solution.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (integer_t)(x).size()

constexpr integer_t n = 200000;
constexpr integer_t k = 398912;
constexpr integer_t q = 200000;
constexpr integer_t sigma = 5;

vector<integer_t> generateInit() {
	vector<integer_t> res(n, 1);
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
		integer_t p, x;
		if (i == 12345) {
			p = 234;
			x = 2;
		} else if (i == 34512) {
			p = 123;
			x = 2;
		} else {
			p = randomInteger<integer_t>(0, state.size() + 1);
			x = 1;
		}
		jout << p << " " << x << endl;
		state.add(p, x);
	}
	jerr << sz(state) << endl;
}
