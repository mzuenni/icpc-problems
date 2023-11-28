#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer w = arguments["--w"].asInteger();
	Integer l = arguments["--("].asInteger(-2) + 1;
	l = arguments["--["].asInteger(l);
	Integer r = arguments["--)"].asInteger(0) - 1;
	r = arguments["--]"].asInteger(r);

	std::vector<Integer> ws = arguments["--ws"].asIntegers();
	for (Integer i = l; i <= r; i++) ws.push_back(i);
	Random::shuffle(ws);

	testOut << ws.size() << " " << w << std::endl;
	testOut << ws << std::endl;
}
