#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::integer(1, 200'001));
	Integer a = arguments["--a"].asInteger(10*Random::binomial(1, 100'001, 100'000, 0.5));
	Integer b = arguments["--b"].asInteger(10*Random::binomial(1, 100'001, 100'000, 0.5));

	testOut << n << std::endl;
	for (Integer i = 0; i < n; i++)
	{
		if (Random::bit())
			std::swap(a, b);
		testOut << a << ' ' << b << '\n';
	}
}
