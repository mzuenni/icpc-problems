#include "validate.h"
using namespace std;

constexpr Integer lim = 1000000;

using pt = complex<Integer>;

struct rect {
	Integer x1, y1, x2, y2;
};

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer limn = arguments["--n"].asInteger(200000);
	Real m = arguments["--m"].asReal(-1.673897312798);
	Real c = arguments["--c"].asReal(13132.42387432);

	auto fx = [=](Integer x){return m*x+c;};
	auto fy = [=](Integer y){return (y-c)/m;};

	//initially fill plane with rectangle
	vector<rect> out = {{1,1,lim-1,lim-1}};

	// randomly divide an rectangle
	for (Integer i = 0; i < 10000000 && out.size() < limn; i++) {
		Integer j = Random::integer(0, out.size());
		swap(out[j], out.back());
		if (Random::bit() == 0) {
			Integer l = max(out.back().x1, (Integer)floor(min(fy(out.back().y1), fy(out.back().y2))));
			Integer r = min(out.back().x2, (Integer)ceil(max(fy(out.back().y1), fy(out.back().y2))));
			if (l + 1 < r) {//vertical cut
				Integer xm = Random::integer(l+1, r);
				rect tmp = out.back();
				out.back().x2 = xm;
				tmp.x1 = xm;
				out.push_back(tmp);
			}
		} else {//horizontal cut
			Integer l = max(out.back().y1, (Integer)floor(min(fx(out.back().x1), fx(out.back().x2))));
			Integer r = min(out.back().y2, (Integer)ceil(max(fx(out.back().x1), fx(out.back().x2))));
			if (l + 1 < r) {
				Integer ym = Random::integer(l+1, r);
				rect tmp = out.back();
				out.back().y2 = ym;
				tmp.y1 = ym;
				out.push_back(tmp);
			}
		}
	}

	Random::shuffle(out);
	testOut << out.size() << endl;
	juryOut << "generated: " << out.size() << endl;
	for (auto r : out) {
		testOut << r.x1 << " ";
		testOut << r.y1 << " ";
		testOut << r.x2 << " ";
		testOut << r.y2 << endl;
	}
}
