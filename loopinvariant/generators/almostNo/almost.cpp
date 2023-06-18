#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer lim = arguments["--lim"].asInteger(Random::integer(1, 1000'000));
	Integer n = arguments["--n"].asInteger(Random::integer(1, 20));
	std::string t, u, s = "(" + Random::bracketSequence(n-1) + ")";

	while (t.size() + u.size() + 2*n + 1 < lim) {
		if (Random::bit()) t += s;//is this efficient?
		else u += s;
	}

	t += "(" + Random::bracketSequence((lim - t.size() - u.size()) / 2 - 1) + ")";

	testOut << t << u << std::endl;
}
