#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::integer(1, 200'001));

	std::vector<std::pair<Integer, Integer>> in(n);
	for (auto& [a, b] : in) {
		a = Random::integer(1, 1'000'001);
		b = Random::integer(1, 1'000'001);
	}

	Random::shuffle(in);
	testOut << n << std::endl;
	testOut << join(in, NEWLINE) << std::endl;
}
