#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::integer(1, 200'001));
	Integer x = arguments["--x"].asInteger(10*Random::binomial(1, 100'001, 100'000, 0.5));
	Integer y = arguments["--y"].asInteger(10*Random::binomial(1, 100'001, 100'000, 0.5));


	if (x < y) std::swap(x, y);
	Integer lower = x * y;
	Integer area = x * y * std::min(x, y);

	std::vector<std::pair<Integer, Integer>> in = {{x, y}};
	for (Integer i = x - 1; i > 0; i--) {
		Integer yy = std::max(y+1, (lower + i - 1) / i);
		if (i * yy * std::min(i, yy) >= area) continue;
		y = yy;
		if (y > 1'000'000) break;
		in.push_back({i, y});
	}
	juryErr << in.size() << std::endl;
	while (in.size() < n) {
		auto a = Random::select(in);
		if (a.second > 1) in.push_back({a.first, Random::integer(1, a.second)});
	}
	while (in.size() > n) in.pop_back();

	Random::shuffle(in);
	for (auto& x : in) Random::shuffle(x);

	testOut << n << std::endl;
	testOut << join(in, NEWLINE) << std::endl;
}
