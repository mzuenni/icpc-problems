#include "validate.h"
using namespace std;

constexpr Integer LIM = 1'000'000;

using pt = complex<Integer>;

struct rect {
	Integer x1, y1, x2, y2;
};

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(200000);
	Integer dx = arguments["--dx"].asInteger(45);
	Integer dy = arguments["--dy"].asInteger(42);
	Integer c = arguments["--c"].asInteger(42639);
	Integer half = LIM / 2;

	vector<rect> out;
	out.push_back({half-1, half+1, half + 1, half+3});// |
	out.push_back({half-3, half-1, half - 1, half+1});// -
	out.push_back({half, half-2, half+2, half});      // #

	/*for (Integer i = 2; out.size() + 2 + 3 <= n; i+=2) {
		out.push_back({half+i, half+i,half+i+2,half+i+2});
		if (i % 4 == 2) {
			out.back().y1--;
			out.back().y2--;
		} else {
			out.back().x1--;
			out.back().x2--;
		}
		out.push_back({half-i-2, half-i-2,half-i,half-i});
		if (i % 4 == 2) {
			out.back().x1++;
			out.back().x2++;
		} else {
			out.back().y1++;
			out.back().y2++;
		}
	}*/

	auto data = Random::distinct(n - 3, -half/2 + 10, half/2 - 10);
	for (auto i : data) {
		i *= 2;
		if (i > 0) {
			out.push_back({half+i, half+i,half+i+2,half+i+2});
			if (i % 4 != 0) {
				out.back().y1--;
				out.back().y2--;
			} else {
				out.back().x1--;
				out.back().x2--;
			}
		} else if (i < 0) {
			out.push_back({half+i-2, half+i-2,half+i,half+i});
			if (i % 4 != 0) {
				out.back().x1++;
				out.back().x2++;
			} else {
				out.back().y1++;
				out.back().y2++;
			}
		}
	}

	Random::shuffle(out);
	for (auto& cur : out) {
		cur.x1 *= dx;
		cur.y1 *= dy;
		cur.x2 *= dx;
		cur.y2 *= dy;

		cur.x1 += c;
		cur.x2 += c;
	}

	testOut << out.size() << endl;
	for (auto r : out) {
		testOut << r.x1 << " ";
		testOut << r.y1 << " ";
		testOut << r.x2 << " ";
		testOut << r.y2 << endl;
	}
}
