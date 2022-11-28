#include "validate.h"
using namespace std;

constexpr Integer LIM = 1'000'000'000;

using pt = complex<Integer>;

struct rect {
	Integer x1, y1, x2, y2;
};

rect mkrect(Integer x1, Integer y1, Integer sizex, Integer sizey, Integer shear) {
	return rect { x1, y1 + shear * x1, x1 + sizex, y1 + shear * x1 + sizey };
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(99999);
	Integer dx = arguments["--dx"].asInteger(27);
	Integer dy = arguments["--dy"].asInteger(22);
	Integer spacing = arguments["--spc"].asInteger(2);
	Integer shear = arguments["--shear"].asInteger(0);
	Integer dcenter = arguments["--dc"].asInteger(0);
	vector<rect> out;
	bool flip = Random::bit();

	out.push_back(mkrect(0, dcenter, 1, 1, shear));

	vector<Integer> xp(n);
	iota(xp.begin(), xp.end(), 0);
	vector<Integer> yp(n);
	iota(yp.begin(), yp.end(), 2);

	Integer cut1 = Random::integer(0, n);
	Integer cut2 = Random::integer(0, n);

	for (int i = 0; i < n; ++i) {
		Integer sizex = 1, sizey = 2 * yp[i] + 1;
		if (i < cut1) {
			out.push_back(mkrect(spacing * xp[i] + 2, -yp[i], sizex, sizey, shear));
		}
		if (i < cut2) {
			out.push_back(mkrect(-spacing * xp[i] - 2, -yp[i], sizex, sizey, shear));
		}
	}

	Integer minx = 0, miny = 0;

	for (auto r : out) {
		minx = min(minx, r.x1);
		minx = min(minx, r.x2);
		miny = min(miny, r.y1);
		miny = min(miny, r.y2);
	}

	for (auto &r : out) {
		r.x1 = r.x1 - minx + dx;
		r.x2 = r.x2 - minx + dx;
		r.y1 = r.y1 - miny + dy;
		r.y2 = r.y2 - miny + dy;
	}

	testOut << out.size() << endl;
	for (auto r : out) {
		if (flip) {
			swap(r.x1, r.y1);
			swap(r.x2, r.y2);
		}

		testOut << r.x1 << " ";
		testOut << r.y1 << " ";
		testOut << r.x2 << " ";
		testOut << r.y2 << endl;
	}
}
