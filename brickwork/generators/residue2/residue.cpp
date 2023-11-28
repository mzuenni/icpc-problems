#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer w = arguments["--w"].asInteger(Random::prime(1, 300001));
	Integer mod = arguments["--mod"].asInteger(Random::prime(1, 50));
	Integer residue = (w * multInv(mod - 1, mod)) % mod;

	std::vector<Integer> ws;
	for (Integer i = mod; i < w; i += mod) ws.push_back(i);
	for (Integer i = residue; i < w; i += mod) {
		if (i * (mod - 1) > w) ws.push_back(i);
	}

	Random::shuffle(ws);

	testOut << ws.size() << " " << w << std::endl;
	testOut << ws << std::endl;
}
