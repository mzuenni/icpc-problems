//can generate possible testcases...
#include "validate.h"

std::pair<Integer, Integer> gen(Integer digits, std::string& cancel, bool doSwap = false) {
	std::string a = std::string(digits - cancel.size(), '*') + cancel;
	Random::shuffle(a.begin(), a.end());
	Integer aa = 0;
	std::vector<std::size_t> index;
	for (std::size_t i = 0; i < a.size(); i++) {
		char& z = a[i];
		if (z == '*') {
			z = Random::select(DIGITS);
			aa *= 10;
			aa += z - '0';
		}
	}
	Random::shuffle(index);
	if (index.size() >= 2) std::swap(a[index[0]], a[index[1]]);
	return {stoll(a), aa};
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);			// initialize streams, rng and parse arguments
	using namespace Generator;

	Integer digits = arguments["--digits"].asInteger(18);
	Integer cancel = arguments["--cancel"].asInteger(Random::integer(1,digits));

	std::string cc(cancel, '*');
	for (char& z : cc) z = Random::select(DIGITS);

	auto [a, c] = gen(digits, cc);
	auto [b, d] = gen(digits, cc, true);

	Integer ma = 999'999'999'999'999'999 / std::max(c, d);
	Integer g = Random::integer(1, ma + 1);
	//a,b,c,d could be 0 but thats unlikely...

	testOut << join({a, b, c*g, d*g}) << std::endl;
}
