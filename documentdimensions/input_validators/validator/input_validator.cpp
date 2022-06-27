#include "mz_validate.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (integer_t)(x).size()

int main(int argc, char **argv) {
	init_val(argc, argv);
	//jerr	error output stream
	//jout	default output stream
	//tin	testcase input (use readToken(), readSpace(), readEOL(), readEOF())
	integer_t n = tin.readInteger(1, 1000001);
	tin.readEOL();
	integer_t sum = 0;
	for (integer_t i = 0; i < n; i++) {
		string word = tin.readToken();
		if (sz(word) > 1000000) cout << "word too long: " << i << exitVerdict(FAIL);
		sum += sz(word);
		for (char c : word) {
			if (c < 'a' || c > 'z') cout << "invalid char: " << c << exitVerdict(FAIL);
		}
		if (i + 1 < n) tin.readSpace();
	}
	if (sum > 1000000) cout << "words too long: " << sum << exitVerdict(FAIL);
	tin.readEOL();
	tin.readEOF();
	return AC;
}
