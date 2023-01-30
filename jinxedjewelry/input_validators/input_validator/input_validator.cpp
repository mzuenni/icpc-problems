#include "validate.h"

int main(int argc, char **argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;

	Integer t = testIn.integer(1, 1'000'001);
	testIn.newline();
	
	Integer sum_n = 0;

	for (Integer i = 0; i < t; i++) {
		Integer n = testIn.integer(1, 100'001);
		testIn.newline();
		if ((sum_n += n) > 1'000'000)
			juryOut << "sum over all n is too large: sum_n = " << sum_n
				<< ", current n = " << n
				<< ", t = " << i+1 << WA;

		auto lengths = testIn.integers(1, 100'000, n);
		testIn.newline();
		
		Integer sum = 0;
		for (Integer x : lengths) sum += x;
		if (sum < 3) juryOut << "too few chainlinks, t=" << i+1 << WA;
	}
	testIn.eof();
	return AC;
}
