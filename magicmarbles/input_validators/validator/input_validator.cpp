#include "mz_validate.h"
#include "solution.h"
using namespace std;

using namespace validator;

#define all(x) begin(x), end(x)
#define sz(x) (integer_t)(x).size()

integer_t maxRun(const vector<integer_t>& in) {
	integer_t res = 0;
	
	integer_t current = in[0];
	integer_t length = 0;
	for (integer_t x : in) {
		if (x != current) {
			current = x;
			length = 0;
		}
		length++;
		res = max(res, length);
	}
	return res;
}

int main(int argc, char **argv) {
	init_val(argc, argv);
	//jerr	error output stream
	//jout	default output stream
	//tin	testcase input (use readToken(), readSpace(), readEOL(), readEOF())
	integer_t n, k, q;
	tin >> INT(1, 200001, n) >> SPACE
		>> INT(2, 400001, k) >> SPACE
		>> INT(1, 200001, q) >> NEWLINE;
	vector<integer_t> m(n);
	tin >> LIST(all(m), INT(1, 1000001)) >> NEWLINE;

	jout << ifTrue(maxRun(m) >= k) << "Too long run in m" << exitVerdict(FAIL);

	marbles state(k);
	for (integer_t i = 0; i < n; i++) state.add(i, m[i]);

	for (integer_t i = 1; i <= q; i++) {
		integer_t p, mx;
		tin >> INT(0, state.size()+1, p) >> SPACE 
			>> INT(1, 1000001, mx) >> NEWLINE;
		state.add(p, mx);
	}
	tin >> ENDFILE;
	return AC;
}
