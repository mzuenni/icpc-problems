#include "mz_validate.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (integer_t)(x).size()

constexpr integer_t n = 200000;
constexpr integer_t q = n;

int main(int argc, char **argv) {
	init_gen(argc, argv);
	//jerr	error output stream
	//jans	generator input (cin)

	//jout	testcase output stream
	//use std::mt19937_64 mz_rng
	jout << n << " 2 " << q << endl;
	vector<integer_t> m(n, 1);
	for (integer_t i = 0; i < n; i+=2) m[i] = 2;
	m.back() = 3;
	jout << outList(all(m)) << endl;
	for (integer_t i = n-2, j = n; i >= 0; i--, j++) {
		jout << j << " " << m[i] << endl; 
	}
	jout << n << " 3" << endl;
}
