#include "validate.h"

std::pair<Integer, Integer> gen(Integer digits, std::string& cancel) {
	std::string a = std::string(digits - cancel.size(), '*') + cancel;
	Random::shuffle(a.begin(), a.end());
	Integer aa = 0;
	for (char& z : a) {
		if (z == '*') {
			z = Random::select(DIGITS);
			aa *= 10;
			aa += z - '0';
		}
	}
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
	auto [b, d] = gen(digits, cc);

	Integer ma = 999'999'999'999'999'999 / std::max(c, d);
	Integer g = Random::integer(1, ma + 1);
	//a,b,c,d could be 0 but thats unlikely...

	testOut << join({a, b, c*g, d*g}) << std::endl;
}
