#include "validate.h"

const std::string ops = "+*?";

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(500'001);
	Integer q = arguments["--q"].asInteger(500'001);

	testOut << n << " " << q << std::endl;
	for (Integer i = 0; i < q; i++) {
		testOut << Random::select(ops) << " " << Random::integer(1, n+1) << std::endl;
	}
}
