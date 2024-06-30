#include "validate.h"

int main(int argc, char **argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;

	Integer n = testIn.integer(1, 200'001);
	testIn.space();
	Integer q = testIn.integer(1, 200'001);
	testIn.space();
	Real p = testIn.realStrict(0, 1, 0, 7);
	if (p == 0) juryOut << "Real " << p << " out of range (" << 0 << ", " << 1 << ")!" << WA;
	testIn.newline();

	std::regex type("[+-?]");
	std::vector<std::multiset<Integer>> state(n+1);
	for (Integer i = 0; i < q; i++) {
		std::string token = testIn.string(type, 1, 2);
		if (token == "?") {
			testIn.space();
			testIn.integer(1, n+1);
			testIn.newline();
		} else {
			testIn.space();
			Integer b = testIn.integer(1, 1'000'000'001);
			testIn.space();
			Integer x = testIn.integer(1, n+1);
			testIn.newline();

			if (token == "+") {
				state[x].insert(b);
			} else {
				auto it = state[x].find(b);
				if (it == state[x].end()) juryOut << "remove non existing lamp, q=" << i+1 << WA;
				state[x].erase(it);
			}
		}
	}
	testIn.eof();
	return AC;
}
