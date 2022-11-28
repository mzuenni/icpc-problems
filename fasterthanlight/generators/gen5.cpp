#include "validate.h"
using namespace std;

constexpr Integer offset = 400'000'000;

using pt = complex<Integer>;

struct rect {
	Integer x1, y1, x2, y2;
};

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer limn = arguments["--n"].asInteger(200000);

	vector<pair<Integer, Integer>> upper;
	for (Integer x = 0, y = 1; y < offset; x++, y += x+1) {
		upper.push_back({x, y});
		upper.push_back({-y, -x});
	}
	sort(upper.begin(), upper.end());
	for (Integer i = 0, x = -upper[0].first, y = -upper[0].second, c = upper.size(); i < c; i++) {
		upper[i].first += x + 1;
		upper[i].second += y + 1;
		upper.push_back({-upper[i].first, upper[i].second});
	}
	sort(upper.begin(), upper.end());
	for (Integer i = 0, x = -upper[0].first; i < upper.size(); i++) {
		upper[i].first += x + 1;
	}
	sort(upper.begin(), upper.end());

	vector<rect> out;
	bool first = true;
	for (auto [x, y] : upper) {
		out.push_back({x, -y + upper[0].second + 4, x+1, y + upper[0].second + 1});
		if (out.back().y1 > out.back().y2) {
			if (first) out.back().y1 -= 2;
			else out.back().y2 += 2;
			first = false;
		}
	}

	Random::shuffle(out);
	juryOut << "generated: " << out.size() << endl;
	while (out.size() > limn) out.pop_back();
	testOut << out.size() << endl;
	for (auto r : out) {
		testOut << r.x1 << " ";
		testOut << r.y1 << " ";
		testOut << r.x2 << " ";
		testOut << r.y2 << endl;
	}
}
