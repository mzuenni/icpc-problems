// generates a big square 
// with a lot of triangles with corners on 3 of the 4 sides of the square
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
	for (Integer i = 0; i < 4; i++) {
		Random::shuffle(border[i]);
	}
	std::vector<line> lines;
	lines.push_back({{dim, dim}, {-dim, dim}});
	lines.push_back({{dim, dim}, {dim, -dim}});
	lines.push_back({{-dim, -dim}, {-dim, dim}});
	lines.push_back({{-dim, -dim}, {dim, -dim}});
	while (lines.size() + 3 <= n) {
		std::vector<Integer> choosen = {0,1,2,3};
		Random::shuffle(choosen);
		choosen[3] = choosen[0];
		for (Integer i = 0; i < 3; i++) {
			lines.push_back({border[choosen[i]].back(), border[choosen[i + 1]].back()});
		}
		for (Integer i = 0; i < 3; i++) {
			border[choosen[i]].pop_back();
		}
	}
	print(lines);
}
