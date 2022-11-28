#include "validate.h"
using namespace std;

constexpr Integer LIM = 1'000'000'000;

using pt = complex<Integer>;

struct rect {
	Integer x1, y1, x2, y2;
};

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(200000);
	Integer dx = arguments["--dx"].asInteger(27);
	Integer dy = arguments["--dy"].asInteger(22);
	Integer c = arguments["--c"].asInteger(125);
	bool flip = arguments["--flip"].exists();

	auto se = Random::increasing(n - 2, 3, LIM / max(dx, dy) - c - 3);
	swap(Random::select(se), se.back());
	vector<rect> out;
	for (Integer i = 0; i + 1 < se.size(); i++) {
		out.push_back({se[i]*dx + c, se[i]*dy, se[i]*dx + c + 1, se[i]*dy+1});
	}
	out.back().y1 += dy + 2;
	out.back().y2 += dy + 2;

	out.push_back({0, 0, 1, LIM});
	out.push_back({LIM-1, 0, LIM, LIM});

	Random::shuffle(out);

	if (flip) {
		for (auto& r : out) {
			swap(r.x1, r.y1);
			swap(r.x2, r.y2);
		}
	}

	testOut << out.size() << endl;
	for (auto r : out) {
		testOut << r.x1 << " ";
		testOut << r.y1 << " ";
		testOut << r.x2 << " ";
		testOut << r.y2 << endl;
	}
}
