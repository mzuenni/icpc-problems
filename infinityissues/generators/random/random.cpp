#include "validate.h"

int main(int argc, char** argv) {
	using namespace Generator;
	Generator::init(argc, argv);

	Integer n = arguments["--n"].asInteger(Random::integer(1, 1001));
	Integer w = arguments["--w"].asInteger(Random::integer(1, 1001));

	std::vector<std::string> line(n);
	for (auto& l : line) {
		l = std::string(Random::integer(1, 101), '*');
		for (auto& c : l) {
			c = Random::select(LOWER);
		}
	}
	testOut << n << " " << w << std::endl;
	testOut << line << std::endl;
}
