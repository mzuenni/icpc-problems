#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer w = arguments["--w"].asInteger(Random::integer(1, 300001));
	Integer n = arguments["--n"].asInteger(Random::integer(1, w*0.75));

    testOut << n << " " << w << std::endl;
    auto tmp = Random::distinct(n, w/4, w+1);
    testOut << tmp << std::endl;
}
