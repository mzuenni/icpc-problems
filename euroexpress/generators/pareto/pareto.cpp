#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::integer(1, 200'001));

	auto a = Random::increasing(n, 1, 1'000'001);
	auto b = Random::decreasing(n, 1, 1'000'001);

	std::vector<std::pair<Integer, Integer>> in(n);
	for (Integer i = 0; i < n; i++) {
		in[i] = {a[i], b[i]};
	}

	Random::shuffle(in);
	testOut << n << std::endl;
	testOut << join(in, NEWLINE) << std::endl;
}
