#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::integer(1, 200'000));
	Integer s = arguments["--s"].asInteger(Random::integer(6*n, 14*n));

	testOut << n << " " << s << std::endl;
    for (int i = 0; i < n; i++)
    {
        testOut << Random::integer(1, 20)*3 + Random::integer(1, 2);
        if (i < n-1) testOut << " ";
    }
    testOut << std::endl;
}
