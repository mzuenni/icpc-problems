#include "validate.h"
using namespace std;

constexpr Integer LIM = 1'000'000'000;

using pt = complex<Integer>;

struct rect {
	Integer x1, y1, x2, y2;
};

rect mkrect(Integer x1, Integer y1, Integer sizex, Integer sizey) {
	return rect { x1, y1, x1 + sizex, y1 + sizey };
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(30000);
	vector<rect> out;

	out.push_back(mkrect(0, -2, 1, 1));
	Integer curx = -2, cury = -8, size = 8;

	bool cutVertTop = Random::integer(10) < 5;
	bool cutVertBot = Random::integer(10) < 5;
	bool cutHorLeft = Random::integer(10) < 5;
	bool cutHorRight = Random::integer(10) < 5;

	Integer cutVertTopStep = Random::integer(n);
	Integer cutVertBotStep = Random::integer(n);
	Integer cutHorLeftStep = Random::integer(n);
	Integer cutHorRightStep = Random::integer(n);

	Integer cutAmount = 40;

	for (int i = 0; i < n; i++) {
		Integer hy = cury;
		Integer hs = size + 10;

		if (cutVertTop && cutVertTopStep == i) {
			hs -= cutAmount;
		}
		if (cutVertBot && cutVertBotStep == i) {
			hs -= cutAmount;
			hy += cutAmount;
		}

		out.push_back(mkrect(curx, hy, 1, hs));

		Integer off = 11;
		curx -= off;
		cury -= 1;
		size += off + 1;

		Integer vx = curx;
		Integer vs = size + 10;

		if (cutHorLeft && cutHorLeftStep == i) {
			vx += cutAmount;
			vs -= cutAmount;
		}
		if (cutHorRight && cutHorRightStep == i) {
			vs -= cutAmount;
		}

		out.push_back(mkrect(vx, cury, vs, 1));
		Integer yoff = Random::integer(3, 20);
		curx -= 1;
		cury -= off;
		size += off + 1;
	}

	Integer minx = 0, miny = 0;

	for (auto r : out) {
		minx = min(minx, r.x1);
		minx = min(minx, r.x2);
		miny = min(miny, r.y1);
		miny = min(miny, r.y2);
	}

	Integer dx = 0, dy = 0;

	for (auto &r : out) {
		r.x1 = r.x1 - minx + dx;
		r.x2 = r.x2 - minx + dx;
		r.y1 = r.y1 - miny + dy;
		r.y2 = r.y2 - miny + dy;
	}

	Random::shuffle(out.begin(), out.end());

	testOut << out.size() << endl;
	for (auto r : out) {
		bool flip = false;
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
