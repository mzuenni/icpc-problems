#include "validate.h"

using bits = std::bitset<190>;

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
	std::reverse(res.begin(), res.end());
	return res;
}

bits bubble(const std::vector<entry>& ops, std::vector<Integer> state) {
	bits res;
	for (Integer i = 0; i < ops.size(); i++) {
		if (state[ops[i].x1] > state[ops[i].x2]) {
			std::swap(state[ops[i].x1], state[ops[i].x2]);
			res[i] = true;
		}
	}
	return res;
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer w = arguments["--w"].asInteger(20);
	Integer h = arguments["--h"].asInteger(200);
	Integer maxQ = arguments["--maxQ"].asInteger(200000);
	judgeAssert(w*(w-1)/2 < h, "h too small!");

	std::vector<entry> ops = genEntries(w);
	std::vector<bits> todo;
	std::vector<Integer> perm(w);
	for (Integer i = 0; i < w; i++) perm[i] = i;
	Integer count = 0;
	bits last;
	while (true) {
		Random::shuffle(perm);
		bits cur = bubble(ops, perm);
		count += (last ^ cur).count();
		if (count > maxQ) break;
		todo.push_back(cur);
		last = cur;
	}
	last.reset();
	std::vector<entry> qs;
	for (auto cur : todo) {
		for (Integer i = 0; i < ops.size(); i++) {
			if (last[i] != cur[i]) qs.push_back(ops[i]); 
		}
		last = cur;
	}

	judgeAssert(qs.size() <= maxQ, "too many queries!");
	testOut << w << " " << h << " " << qs.size() << std::endl;
	for (auto e : qs) e.print();
}
