#include "validate.h"

const std::string ops = "+*";

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::minimum(1, 500'001, 2));
	Integer q = arguments["--q"].asInteger(500'001 / (n + 1));
	judgeAssert((n+1)*q <= 500'000, "Too large values for n,q");

	testOut << n << " " << (n+1) * q << std::endl;
	for (Integer i = 0; i < q; i++) {
		testOut << Random::select(ops) << " " << Random::integer(1, n+1) << std::endl;
		for (Integer j = 1; j <= n; j++) {
			testOut << "? " << j << std::endl;
		}
	}
}
