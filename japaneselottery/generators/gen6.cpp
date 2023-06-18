#include "validate.h"

struct entry {
	Integer y, x1, x2;
	void print() {
		using namespace Generator;
		testOut << y+1 << " " << x1+1 << " " << x2+1 << std::endl;
	}
};

std::vector<entry> genEntries(Integer w) {
	std::vector<entry> res;
	Integer y = 0;
	for (Integer i = w; i >= 0; i--) {
		for (Integer j = 0; j + 1 < i; j++) {
			res.push_back({y, j, j+1});
			y++;
		}
	}
	return res;
}

Integer grayCode(Integer x) {
	return x ^ (x >> 1);
}


int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer w = arguments["--w"].asInteger(6);
	Integer h = arguments["--h"].asInteger(20);
	Integer maxQ = arguments["--maxQ"].asInteger(200000);
	judgeAssert(w*(w-1)/2 < h, "h too small!");

	std::vector<entry> ops = genEntries(w);
	std::vector<entry> qs;
	Integer last = 0;
	for (Integer i = 1; i < (1ll << ops.size()); i++) {
		Integer cur = grayCode(i);
		Integer flip = std::__lg(cur ^ last);
		qs.push_back(ops[flip]);
		last = cur;
	}

	judgeAssert(qs.size() <= maxQ, "too many queries!");
	testOut << w << " " << h << " " << qs.size() << std::endl;
	for (auto e : qs) e.print();
}
