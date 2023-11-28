// generates many intersections...
#include "validate.h"

using pt = std::pair<Integer, Integer>;
using line = std::pair<pt, pt>;

void print(std::vector<line>& lines) {
	using namespace Generator;
	Random::shuffle(lines);
	testOut << lines.size() << std::endl;
	testOut << join(lines, NEWLINE) << std::endl;
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer dim = arguments["--dim"].asInteger(1000000-7);
	Integer n = arguments["--n"].asInteger(1000);
	n /= 3;

	auto a = Random::increasing(n, 1, dim);
	auto b = Random::increasing(n, 1, dim);
	auto c = Random::increasing(n, 1, dim);

	std::vector<line> lines;
	for (Integer i = 0; i < n; i++) {
		lines.push_back({{0, a[i]}, {b[i], -b[i]}});
		lines.push_back({{-c[i], -c[i]}, {b[i], -b[i]}});
		lines.push_back({{0, a[i]}, {-c[i], -c[i]}});
	}

	print(lines);
}
