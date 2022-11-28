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
	Integer dx = arguments["--dx"].asInteger(22);
	Integer dy = arguments["--dy"].asInteger(27);
	Integer c = arguments["--c"].asInteger(125);

	auto se = Random::increasing(2*n-2, 0, LIM / max(dx, dy) - c);
	vector<rect> out;
	for (Integer i = 0; i < se.size(); i+=2) {
		out.push_back({se[i]*dx + c, se[i]*dy, se[i+1]*dx + c, se[i+1]*dy});
	}
	rect o = Random::select(out);
	out.push_back({o.x2, Random::integer(0, o.y1), Random::integer(o.x2+1, LIM), o.y1});

	Random::shuffle(out);

	testOut << out.size() << endl;
	for (auto r : out) {
		testOut << r.x1 << " ";
		testOut << r.y1 << " ";
		testOut << r.x2 << " ";
		testOut << r.y2 << endl;
	}
}
