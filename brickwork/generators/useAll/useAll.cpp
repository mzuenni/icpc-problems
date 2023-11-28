#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::integer(1, 14));

	std::vector<Integer> ws;
	for (Integer i = 0; i < n; i++) ws.push_back(3 * (1ll << i));
	std::reverse(ws.begin(), ws.end());
	for (Integer i = 0; i < 2 && i < n; i++) ws[i] /= 3;
	std::partial_sum(ws.begin(), ws.end(), ws.begin());
	Random::shuffle(ws);

	Integer w = ((1ll << (n-1)) * (3*n - 4) + 3);

	testOut << n << " " << w << std::endl;
	testOut << ws << std::endl;
}
