#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer w = arguments["--w"].asInteger(Random::integer(3, 199'998));
	w -= w % 3;

	std::vector<Integer> ws = {w / 3, w / 3 * 2};
	for (Integer i = ws[0] + 1, j = ws[1] - 1; i < j; i++, j--) {
		ws.push_back(Random::integer(3) == 0 ? j : i);
	}
	Random::shuffle(ws);

	testOut << ws.size() << " " << w << std::endl;
	testOut << ws << std::endl;
}
