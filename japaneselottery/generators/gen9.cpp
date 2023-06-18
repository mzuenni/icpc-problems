#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer w = arguments["--w"].asInteger(20);
	Integer h = arguments["--h"].asInteger(200000);
	Integer step = arguments["--step"].asInteger(Random::integer(200, 2000));
	Integer q = arguments["--q"].asInteger(200000);

	Integer p = h;
	while (!isPrime(p)) p--;

	testOut << w << " " << h << " " << h << std::endl;
	for (Integer i = 0; i < p; i++) {
		Integer x1 = Random::integer(0, w-1);
		Integer x2 = x1 + 1;
		if (Random::bit()) std::swap(x1, x2);
		testOut << (1 + ((i * step) % p)) << " " << x1+1 << " " << x2+1<< std::endl;
	}
	for (Integer i = p; i < h; i++) {
		Integer x1 = Random::integer(0, w-1);
		Integer x2 = x1 + 1;
		if (Random::bit()) std::swap(x1, x2);
		testOut << i+1 << " " << x1+1 << " " << x2+1<< std::endl;
	}
}
