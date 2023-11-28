#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::integer(1, 200'000));
	Integer s = arguments["--s"].asInteger(Random::integer(1, 1'000'000'000));

	testOut << n << " " << s << std::endl;
	testOut << join(Random::multiple(n, 3, std::min((2*2*3*s)/n, 1'000'000'000_int))) << std::endl;
}
