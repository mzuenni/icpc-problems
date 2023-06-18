#include "validate.h"

struct entry {
	Integer y, rand;
	bool operator<(const entry& o) const {
		return rand < o.rand;
	}
};

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer w = arguments["--w"].asInteger(20);
	Integer h = arguments["--h"].asInteger(200000);
	Integer q = arguments["--q"].asInteger(200000);
	Integer p = arguments["--p"].asReal(0.25);


	testOut << w << " " << h << " " << q << std::endl;
	std::vector<Integer> state(h, -1);
	std::priority_queue<entry> toDel, toIns;

	auto add = [&](){
		Integer y = toIns.top().y;
		toIns.pop();
		Integer x1 = Random::integer(0, w-1);
		Integer x2 = x1 + 1;
		state[y] = x1;
		toDel.push({y, Random::integer()});
		if (Random::bit()) std::swap(x1, x2);
		testOut << y+1 << " " << x1+1 << " " << x2+1 << std::endl;
	};

	auto del = [&](){
		Integer y = toDel.top().y;
		toDel.pop();
		Integer x1 = state[y];
		Integer x2 = x1 + 1;
		state[y] = -1;
		toIns.push({y, Random::integer()});
		if (Random::bit()) std::swap(x1, x2);
		testOut << y+1 << " " << x1+1 << " " << x2+1 << std::endl;
	};

	for (Integer i = 0; i < h; i++) toIns.push({i, Random::integer()});
	for (Integer i = 0; i < q; i++) {
		if (toDel.empty()) add();
		else if (toIns.empty()) del();
		else if (Random::real() < p) del();
		else add();
	}
}
