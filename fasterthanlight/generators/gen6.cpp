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
	Integer mMul = arguments["--mMul"].asInteger(13);
	Integer mDiv = arguments["--mDiv"].asInteger(17);
	Integer offset = arguments["--c"].asInteger(125);

	Integer step = mMul * mDiv;
	Integer c = Random::integer(0, step);

	vector<rect> out;
	vector<Integer> js = Random::distinct(n, 1, LIM/(step*2));
	for (Integer j : js) {
		Integer size = 1;
		for (Integer k = j; (k & 1) == 0; k /= 2) size *= 2;
		size = Random::integer(1, size + 1);
		Integer x = j * step + c;
		Integer y = ((j + offset) * step * mMul) / mDiv;
		if (Random::integer(4) == 0) {
			out.push_back({x, y-size, x+size, y});//lower
		} else {
			out.push_back({x-size, y, x, y+size});//upper
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
