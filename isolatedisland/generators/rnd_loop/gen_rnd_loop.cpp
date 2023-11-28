// generates a random loop (4 regular graph)
// this may take some time since it needs n^2log(n) operations
// if dim is big enough we could make checkPoint() always true
// the probability for three points on a line will be small...
//
// testcase could be invalid (not connected) but thats unlikely
#include "validate.h"

using pt = std::pair<Integer, Integer>;
using line = std::pair<pt, pt>;

void print(std::vector<line>& lines) {
	using namespace Generator;
	Random::shuffle(lines);
	testOut << lines.size() << std::endl;
	testOut << join(lines, NEWLINE) << std::endl;
}

Integer gcd(Integer a, Integer b) { return b == 0 ? a : gcd(b, a % b); }

bool checkPoint(pt p, const std::vector<pt>& ps) {
	std::set<pt> seen;
	for (pt c : ps) {
		Integer dx = c.first - p.first;
		Integer dy = c.second - p.second;
		if (dx == 0 && dy == 0) return false;
		Integer d = gcd(dx, dy);
		dx /= d;
		dy /= d;
		if (seen.find({dx, dy}) != seen.end()) return false;
		seen.insert({dx, dy});
	}
	return true;
}


int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer dim = arguments["--dim"].asInteger(1000000-7);
	Integer n = arguments["--n"].asInteger(1000);

	std::vector<pt> ps;
	while (ps.size() < n) {
		Integer x = Random::integer(-dim, dim + 1);
		Integer y = Random::integer(-dim, dim + 1);
		if (checkPoint({x, y}, ps)) {
			ps.push_back({x, y});
		}
	}

	Random::shuffle(ps);
	std::vector<line> lines;
	for (Integer i = 0; i < n; i++) {
		lines.push_back({ps[i], ps[(i+1) % n]});
	}
	print(lines);
}
