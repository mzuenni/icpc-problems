#include "validate.h"

int main(int argc, char** argv) {
	using namespace Generator;
	Generator::init(argc, argv);

	Integer suits = 4;

	auto arg = arguments["--n"];
	std::string chars = "chds";
	std::vector<Integer> numbers;
	std::vector<Real> means;
	std::vector<Real> stddevs;

	for(Integer i = 0; i < suits; i++) numbers.push_back(arg[i].asInteger());
	for(Integer i = suits; i < 2 * suits; i++) means.push_back(arg[i].asReal());
	for(Integer i = 2 * suits; i < 3 * suits; i++) stddevs.push_back(arg[i].asReal());

	std::vector<std::pair<Real, Integer>> samples;

	for(Integer suit = 0; suit < 4; suit++) {
		for(Integer i = 0; i < numbers[suit]; i++) {
			Real sample = Random::normal(-1e6, 1e6, means[suit], stddevs[suit]);
			samples.push_back({sample, suit});
		}
	}

	std::sort(samples.begin(), samples.end());
	std::string s = "";
	for(auto x : samples) s += chars[x.second];
	testOut << s << std::endl;
}
