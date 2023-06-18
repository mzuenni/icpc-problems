#include "validate.h"

int main(int argc, char **argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;

	Integer w = testIn.integer(2, 21);
	testIn.space();
	Integer h = testIn.integer(1, 200001);
	testIn.space();
	Integer q = testIn.integer(1, 200001);
	testIn.newline();

	std::vector<Integer> lx(h+1, -1);

	for (Integer t = 0; t < q; t++) {
		Integer y = testIn.integer(1, h+1);
		testIn.space();
		Integer x1 = testIn.integer(1, w+1);
		testIn.space();
		Integer x2 = testIn.integer(1, w+1);
		testIn.newline();

		if (std::abs(x1-x2) != 1) juryOut << "|x1-x2| != 1, for q=" << t+1 << WA;

		Integer x = std::min(x1, x2);
		if (lx[y] < 0) {
			lx[y] = x;
		} else if (lx[y] == x) {
			lx[y] = -1;
		} else {
			juryOut << "two bars at same height, for q=" << t+1 << WA;
		}
	}
	testIn.eof();
	return AC;
}
