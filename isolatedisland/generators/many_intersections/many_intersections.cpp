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
	Integer o = arguments["--o"].asInteger(0);
	n /= 4;

	auto a = Random::increasing(n, 1, dim);
	auto b = Random::decreasing(n, 1, dim);
	auto c = Random::decreasing(n, 1, dim);
	auto d = Random::increasing(n, 1, dim);

	std::vector<line> lines;
	for (Integer i = 0; i < n; i++) {
		lines.push_back({{o, a[i]+o}, {b[i]+o, o}});
		lines.push_back({{o, -d[i]+o}, {b[i]+o, o}});
		lines.push_back({{o, -d[i]+o}, {-c[i]+o, o}});
		lines.push_back({{o, a[i]+o}, {-c[i]+o, o}});
	}

	print(lines);
}
