#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer w = arguments["--w"].asInteger(Random::prime(1, 300001));
	Integer mod = arguments["--mod"].asInteger(Random::prime(1, 50));

	std::vector<Integer> ws;
	for (Integer i = mod; i < w; i += mod) ws.push_back(i);
	for (Integer i = w - 1; 2*i > w; i--) {
		if (i % mod != 0 && i % mod != w % mod) ws.push_back(i);
	}

	Random::shuffle(ws);

	testOut << ws.size() << " " << w << std::endl;
	testOut << ws << std::endl;
}
