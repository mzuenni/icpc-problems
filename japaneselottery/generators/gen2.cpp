#include "validate.h"

struct entry {
	Integer y, x1, x2;
	void print() {
		using namespace Generator;
		if (Random::bit()) std::swap(x1, x2);
		testOut << y+1 << " " << x1+1 << " " << x2+1 << std::endl;
	}
};

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer w = arguments["--w"].asInteger(20);
	Integer h = arguments["--h"].asInteger(100000);
	Integer q = arguments["--q"].asInteger(2*h);

	testOut << w << " " << h << " " << q << std::endl;
	std::vector<entry> todo(h);
	for (Integer i = 0; i < h; i++) {
		Integer x1 = Random::integer(0, w - 1);
		todo[i] = {i, x1, x1+1};
	}
	Random::shuffle(todo);
	for (auto e : todo) e.print();
	Random::shuffle(todo);
	for (auto e : todo) e.print();
}
