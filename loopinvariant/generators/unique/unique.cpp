#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer lim = arguments["--lim"].asInteger(Random::integer(1, 1000'000));
	Integer n = arguments["--n"].asInteger(Random::integer(1, 20));
	std::string t, s = "(" + Random::bracketSequence(n - 1) + ")";

	while (t.size() + 2*n <= lim) t += s;//is this efficient?

	testOut << t << std::endl;
}
