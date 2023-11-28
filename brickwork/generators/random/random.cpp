#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::integer(1, 300000));
	Integer w = arguments["--w"].asInteger(Random::integer(n, 300001));

    testOut << n << " " << w << std::endl;
    auto tmp = Random::distinct(n, 1, w+1);
    testOut << tmp << std::endl;
}
