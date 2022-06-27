#include "mz_validate.h"
#include <bits/stdc++.h>
using namespace std;

using namespace validator;

#define all(x) begin(x), end(x)
#define sz(x) (integer_t)(x).size()

int main(int argc, char **argv) {
	init_val(argc, argv);
	//jerr	error output stream
	//jout	default output stream
	//tin	testcase input (use readToken(), readSpace(), readEOL(), readEOF())

	integer_t n, m;
	tin >> INT(3, 100001, n) >> SPACE >> INT(0, 200001, m) >> NEWLINE;
	set<pair<integer_t, integer_t>> seen;
	for (integer_t i = 0; i < m; i++) {
		integer_t a, b;
		tin >> INT(1, n+1, a) >> SPACE 
			>> INT(1, n+1, b) >> NEWLINE;
		if (a >= b) jout << "invalid edge: " << a << " " << b << exitVerdict(FAIL);
		if (seen.count({a, b}) > 0) jout << "duplicated edge: " << a << " " << b << exitVerdict(FAIL);
		seen.insert({a, b});
	}
	tin >> ENDFILE;
	return AC;
}
