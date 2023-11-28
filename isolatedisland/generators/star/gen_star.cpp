// generates an almost star...
#include "validate.h"

using pt = std::pair<Integer, Integer>;
using line = std::pair<pt, pt>;

void print(std::vector<line>& lines) {
	using namespace Generator;
	Random::shuffle(lines);
	testOut << lines.size() << std::endl;
	testOut << join(lines, NEWLINE) << std::endl;
}

Integer left(pt p) {return p.first < 0 || (p.first == 0 && p.second < 0);}
Integer cross(pt a, pt b) {return a.first*b.second-a.second*b.first;};


void sortArround(std::vector<pt>& ps) {
	std::sort(ps.begin(), ps.end(), [&](const pt& a, const pt& b){
		if (left(a) != left(b)) return left(a) > left(b);
		return cross(a, b) > 0;
	});
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer dim = arguments["--dim"].asInteger(1000000-7);
	Integer n = arguments["--n"].asInteger(1000);
	Integer o = arguments["--o"].asInteger(0);
	n -= 4;

	std::vector<pt> border;
	for (Integer i = -dim + 2; i + 2 < dim; i+=3) {
		border.push_back({dim-1, i});
		border.push_back({i, dim-1});
	}
	Random::shuffle(border);
	std::vector<line> lines;
	lines.push_back({{dim, dim}, {dim, -dim}});
	lines.push_back({{dim, dim}, {-dim, dim}});
	lines.push_back({{-dim, -dim}, {dim, -dim}});
	lines.push_back({{-dim, -dim}, {-dim, dim}});
	std::vector<pt> ps;
	for (Integer i = 0; i < border.size() && (lines.size()+1) * 2 <= n; i++) {
		pt a = border[i];
		pt b = {-a.first, -a.second};
		Integer d = Random::select({-1,0,0,0,0,0,1});
		if (b.first == -dim) b.second += d;
		if (b.second == -dim) b.first += d;
		lines.push_back({a, b});
		ps.push_back(a), ps.push_back(b);
	}
	sortArround(ps);
	for (Integer i = 0; i < ps.size(); i+=2) {
		lines.push_back({ps[i], ps[i + 1]});
	}
	for (auto& [a, b] : lines) {
		a.first += o;
		a.second += o;
		b.first += o;
		b.second += o;
	}
	print(lines);
}
