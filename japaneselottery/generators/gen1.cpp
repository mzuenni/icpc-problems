#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer w = arguments["--w"].asInteger(20);
	Integer h = arguments["--h"].asInteger(21845);
	Integer q = arguments["--q"].asInteger(200000);

	testOut << w << " " << h << " " << q << std::endl;
	std::vector<Integer> state(h, -1);
	for (Integer i = 0; i < q; i++) {
		Integer y = Random::integer(0, h);
		Integer x1, x2;
		if (state[y] < 0) {
			x1 = Random::integer(0, w - 1);
			x2 = x1 + 1;
			state[y] = x1;
		} else {
			x1 = state[y];
			x2 = x1 + 1;
			state[y] = -1;
		}
		if (Random::bit()) std::swap(x1, x2);
		testOut << y+1 << " " << x1+1 << " " << x2+1 << std::endl;
	}
}
