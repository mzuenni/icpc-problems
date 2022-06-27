#include "mz_validate.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (integer_t)(x).size()

constexpr integer_t n = 200000;
constexpr integer_t q = 200000;

int main(int argc, char **argv) {
	init_gen(argc, argv);
	//jerr	error output stream
	//jans	generator input (cin)

	//jout	testcase output stream
	//use std::mt19937_64 mz_rng

	integer_t x = n+q;
	//k+2(k-1) <= x;
	//3k-2 <= x;
	//3k <= x+2
	integer_t k = (x+2)/3;
	jout << n << " " << k << " " << q << endl;
	vector<integer_t> state;

	integer_t c = 0;
	for (; c + 1 < k; c++) state.push_back(1);
	c = 0;
	for (; sz(state) < n; c++) state.push_back(2);
	jout << outList(all(state)) << endl;
	for (; c + 1 < k; c++) {
		jout << sz(state) << " 2" << endl;
		state.push_back(2);
	}
	c = 0;
	for (; c + 1 < k; c++) {
		jout << sz(state) << " 1" << endl;
		state.push_back(2);
	}
	jout << n << " 2" << endl;
}
