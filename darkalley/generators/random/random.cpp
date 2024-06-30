namespace Settings {
	int DEFAULT_PRECISION = 6;
}
#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer cn = arguments["--n"].asInteger(Random::integer(1, 200'001));
	Integer cq = arguments["--q"].asInteger(200'000);
	Real cp = arguments["--p"].asReal(Random::real(0.000'001, 1));

	testOut << cn << " " << cq << " " << cp << std::endl;
	std::vector<std::pair<Integer, Integer>> placed;
	for (Integer i = 0; i < cq; i++) {
		Integer type = Random::integer(0, 2 + !placed.empty());
		if (type == 0) {
			Integer cl = Random::integer(1, 1'000'000'001);
			Integer x = Random::integer(0, cn);
			placed.push_back({cl, x});
			testOut << "+ " << cl << " " << x+1 << std::endl;
		} else if (type == 1) {
			Integer x = Random::integer(0, cn);
			testOut << "? " << x+1 << std::endl;
		} else {
			Integer x = Random::integer(0, placed.size());
			swap(placed[x], placed.back());
			testOut << "- " << placed.back().first << " " << placed.back().second+1 << std::endl;
			placed.pop_back();
		}
	}
}
