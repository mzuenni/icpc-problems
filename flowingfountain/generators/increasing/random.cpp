#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::integer(1, 300'001));
	Integer q = arguments["--q"].asInteger(Random::integer(1, 300'001));
	Integer lim = arguments["--lim"].asInteger(1'000'000'000);

	testOut << n << " " << q << std::endl;
	testOut << Random::increasing(n, 1, lim) << std::endl;
	for (Integer i = 0; i < q; i++) {
		if (Random::bit()) testOut << "+ " << 1 << " " << Random::integer(1, lim) << std::endl;
		else testOut << "? " << Random::integer(1, n+1) << std::endl;
	}
}
