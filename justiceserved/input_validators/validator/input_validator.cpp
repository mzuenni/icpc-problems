#include "validate.h"
using namespace std;

int main(int argc, char** argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;
	// juryErr	error output stream
	// juryOut	default output stream
	// testIn	testcase input

	Integer n = testIn.integer(1, 200001, constraint["n"]);
	testIn.newline();
	set<pair<Integer, Integer>> seen;
	for(Integer i = 0; i < n; i++) {
		Integer l = testIn.integer(1, 1000000001, constraint["a"]);
		testIn.space();
		Integer length = testIn.integer(1, 1'000'000'000 + 1, constraint["t"]);
		testIn.newline();
		if(seen.count({l, length}) > 0)
			juryOut << "duplicate interval i=" << i << " : " << l << " len " << length << WA;
		seen.insert({l, length});
	}
	testIn.eof();
	return AC;
}
