#include "validate.h"

int main(int argc, char **argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;

	Integer n = testIn.integer(1, 200'001);
	testIn.space();
	Integer m = testIn.integer(1, 1'000'001);
	testIn.newline();

	Integer realM = 0;
	for (Integer i = 0; i < n; i++) {
		Integer cost = testIn.integer(1, 1'000'001);
		testIn.space();
		Integer length = testIn.integer(1, 1'000'001);
		testIn.newline();
		realM += length;
	}
	testIn.eof();
	if (m != realM) juryOut << "m is wrong, should be: " << realM << WA;
	return AC;
}
