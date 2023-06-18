#include "validate.h"

std::basic_string<Integer> randomPerm(Integer w) {
	auto perm = Random::perm(w);
	std::basic_string<Integer> res;
	for (Integer i = w; i >= 0; i--) {
		for (Integer j = 0; j + 1 < w; j++) {
			if (perm[j+1] < perm[j]) {
				std::swap(perm[j], perm[j + 1]);
				res.push_back(j);
			}
		}
	}
	std::reverse(res.begin(), res.end());
	return res;
}

struct entry {
	Integer y, x1, x2;
	void print() {
		using namespace Generator;
		if (Random::bit()) std::swap(x1, x2);
		testOut << y+1 << " " << x1+1 << " " << x2+1 << std::endl;
	}
};

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer w = arguments["--w"].asInteger(20);
	Integer h = arguments["--h"].asInteger(200000);
	Integer h2 = arguments["--h2"].asInteger(50000);
	Integer q1 = arguments["--q1"].asInteger(100000);
	Integer q2 = arguments["--q2"].asInteger(100000);

	judgeAssert(q1+q2 <= 200000, "too many queries");
	judgeAssert(q1 + h2 <= h, "too many queries");

	testOut << w << " " << h << " " << q1+q2 << std::endl;
	std::basic_string<Integer> first, last;
	while(first.size() + last.size() < q1) {
		first += randomPerm(w);
		last += randomPerm(w);
	}
	Integer hl = first.size();
	Integer hr = h - (Integer)last.size();

	judgeAssert(hl + h2 <= hr, "fail");

	std::vector<entry> fixed;
	for (Integer i = 0; i < first.size(); i++) {
		fixed.push_back({i, first[i], first[i] + 1});
	}
	for (Integer i = 0; i < last.size(); i++) {
		fixed.push_back({hr + i, last[i], last[i] + 1});
	}
	Random::shuffle(fixed);


	std::vector<Integer> state(h2, -1);
	std::vector<entry> mid;
	while (mid.size() + fixed.size() < q1 + q2) {
		Integer x, y = Random::integer(0, h2);
		if (state[y] < 0) {
			x = Random::integer(0, w - 1);
			state[y] = x;
		} else {
			x = state[y];
			state[y] = -1;
		}
		mid.push_back({hl + y, x, x + 1});
	}

	for (auto e : fixed) e.print();
	for (auto e : mid) e.print();
}
