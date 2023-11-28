// generates a big square
// with horizontal and vertial zig zag lines
// ___________________
// |     /\        / |
// |    /  \      /  |
// |   /    \    /   |
// |  /      \  /    |
// |_/________\/_____|
#include "validate.h"

using pt = std::pair<Integer, Integer>;
using line = std::pair<pt, pt>;

void print(std::vector<line>& lines) {
	using namespace Generator;
	Random::shuffle(lines);
	testOut << lines.size() << std::endl;
	testOut << join(lines, NEWLINE) << std::endl;
}

std::vector<pt> zip(const std::vector<pt>& a, const std::vector<pt>& b) {
	std::vector<pt> c;
	for (Integer i = 0; i < a.size() && i < b.size(); i++) {
		c.push_back(a[i]);
		c.push_back(b[i]);
	}
	return c;
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer dim = arguments["--dim"].asInteger(1000000-7);
	Integer n = arguments["--n"].asInteger(1000);

	std::vector<std::vector<pt>> border(4);
	for (Integer i = -dim + 1; i < dim; i++) {
		border[0].push_back({-dim, i});
		border[1].push_back({ dim, i});
		border[2].push_back({i,-dim});
		border[3].push_back({i, dim});
	}
	std::vector<line> lines;
	lines.push_back({{dim, dim}, {-dim, dim}});
	lines.push_back({{dim, dim}, {dim, -dim}});
	lines.push_back({{-dim, -dim}, {-dim, dim}});
	lines.push_back({{-dim, -dim}, {dim, -dim}});
	Integer todo = (n - lines.size() - 2) / 2;
	if (todo % 2 == 0) todo--;
	if (todo <= 1) juryErr << "too few lines" << FAIL;
	for (Integer i = 0; i < 4; i++) {
		Random::shuffle(border[i]);
		border[i].erase(border[i].begin() + ((todo + 1) / 2), border[i].end());
		sort(border[i].begin(), border[i].end());
	}
	for (Integer i = 0; i < 4; i+=2) {
		auto tmp = zip(border[i], border[i+1]);
		for (Integer j = 1; j < tmp.size(); j++) {
			if (tmp[j - 1].first != -tmp[j].first &&
				tmp[j - 1].second != -tmp[j].second) {
				juryErr << "what??" << FAIL;
			}
			lines.push_back({tmp[j - 1], tmp[j]});
		}
		lines.push_back({tmp[0], tmp.back()});
	}
	print(lines);
}
