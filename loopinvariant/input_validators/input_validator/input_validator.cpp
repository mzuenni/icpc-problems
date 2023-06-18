#include "validate.h"

int main(int argc, char **argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;

	std::string s = testIn.string(std::regex("[()]*"), 2, 1'000'001);
	testIn.newline();
	testIn.eof();

	Integer cur = 0;
	for (char c : s) {
		if (c == '(') cur++;
		else cur--;
		if (cur < 0) juryOut << "too many closing brackets" << WA;
	}
	if (cur > 0) juryOut << "too many opening brackets" << WA;
	return AC;
}
