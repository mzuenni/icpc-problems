#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer w = arguments["--w"].asInteger(Random::prime(500, 300001));
	Integer mod = arguments["--mod"].asInteger(Random::prime(300, 500));
	Integer lim = arguments["--lim"].asInteger(2);
	Integer residue = (w * multInv(mod - 1, mod)) % mod;

	std::vector<Integer> ws;
	for (Integer i = residue; i < w; i += mod) {
		if (i * (mod - 1) > w) ws.push_back(i);
	}

	std::vector<bool> possible(w+1);
	possible[0] = true;
	for (Integer x : ws) {
		for (Integer i = x; i <= w; i++) {
			possible[i] = possible[i] | possible[i-x];
		}
	}

	for (Integer i = w; lim*i > w; i--) {
		if (!possible[w - i]) ws.push_back(i);
	}


	Random::shuffle(ws);


	testOut << ws.size() << " " << w << std::endl;
	testOut << ws << std::endl;
}
