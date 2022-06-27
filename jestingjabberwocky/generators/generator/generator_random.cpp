#include "validate.h"

constexpr std::string_view chars = "cdhs";

int main(int argc, char** argv) {
	using namespace Generator;
	Generator::init(argc, argv);

	Integer n = arguments["--n"].asInteger(Random::integer(1, 100001));
	std::string s(n, '*');

	for (char& c : s) c = Random::select(chars.begin(), chars.end());
	testOut << s << std::endl;
}
