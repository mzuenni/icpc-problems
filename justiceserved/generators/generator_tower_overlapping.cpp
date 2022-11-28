#include "validate.h"
using namespace std;

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer tower = arguments["--tower"].asInteger(100000);
	Integer overlapping = arguments["--overlapping"].asInteger(100000);
	Integer noice = arguments["--noice"].asInteger(100);

	auto left = Random::increasing(tower + overlapping, 1, 100'000'000);
	auto right = Random::increasing(overlapping, 100'000'000, 200'000'000);
	append(right, Random::decreasing(tower, 200'000'000, 300'000'000));
	for (Integer i = 0; i < noice; i++) {
		std::swap(Random::select(left), Random::select(left));
	}

	std::vector<std::pair<Integer, Integer>> out(tower + overlapping);
	for (Integer i = 0; i < tower + overlapping; i++) {
		out[i] = {left[i], right[i] - left[i]};
	}
	Random::shuffle(out);

	testOut << out.size() << endl;
	testOut << join(out, '\n') << endl;
}
