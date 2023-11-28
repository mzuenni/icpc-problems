#include "validate.h"

#include <cassert>

const std::regex pmq("[\\+\\*\\?]", std::regex_constants::optimize);

int main(int argc, char** argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;

	Integer n = testIn.integer(2, 500001, constraint["n"]);
	testIn.space();
	Integer q = testIn.integer(2, 500001, constraint["q"]);
	testIn.newline();

	for(Integer i = 0; i < q; i++) {
		std::string type = testIn.string(pmq, 1, 2, constraint["type"]);
		testIn.space();
		if(type == "+") {
			testIn.integer(1, n + 1, constraint["x+"]);
		} else if(type == "*") {
			testIn.integer(1, n + 1, constraint["x*"]);
		} else if(type == "?") {
			testIn.integer(1, n + 1, constraint["x?"]);
		} else {
			assert(false);
		}
		testIn.newline();
	}
	testIn.eof();
	return AC;
}
