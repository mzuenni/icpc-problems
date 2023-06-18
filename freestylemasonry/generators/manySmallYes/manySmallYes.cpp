#include "validate.h"

constexpr std::array<Integer, 5> SEP = {1, 1, 2, 1, 1};

bool check(std::vector<Integer> in) {
	in.push_back(0);
	for (Integer i = 0, j = 0; i < in.size(); i++) {
		if (j > in[i]) return false;
		if ((in[i] - j) % 2 == 0) {
			j = std::max(0_int, j - 1);
		} else {
			j++;
		}
	}
	return true;
}

std::vector<Integer> genYes(Integer w, Integer h) {
	std::vector<Integer> tmp;
	do {
		tmp = Random::multiple(w, 1, h+1);
	} while(!check(tmp));
	return tmp;
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	auto lim = arguments["--lim"].asInteger(200'000);
	auto w = arguments["--w"].asInteger(Random::integer(2, 50));
	auto h = arguments["--h"].asInteger(1'000'000);

	std::vector<Integer> res;
	while (res.size() + w + SEP.size() <= lim) {
		if (!res.empty()) append(res, SEP);
		append(res, genYes(w, h));
	}

	for (Integer& x : res) x = h - x;

	testOut << res.size() << " " << h << std::endl;
	testOut << join(res) << std::endl;
}
