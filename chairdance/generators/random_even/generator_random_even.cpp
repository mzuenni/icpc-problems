#include "validate.h"

const std::string ops = "+*?";

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = 2*arguments["--n"].asInteger(Random::minimum(1, 250'000));
	Integer q = arguments["--q"].asInteger(500'001);

	testOut << n << " " << q << std::endl;
	for (Integer i = 0; i < q; i++) {
		testOut << Random::select(ops) << " " << Random::integer(1,n/2+1)*2 << std::endl;
	}
}
