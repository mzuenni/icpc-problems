#include "validate.h"

int main(int argc, char** argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::integer(10, 200'000));
	Integer s = arguments["--s"].asInteger(Random::integer(1, 999'600'000));

	Integer n_large  = n * 0.1;
	Integer n_small  = n * 0.6;
	Integer n_random = n - n_large - n_small;
	Integer s_large  = s * 0.8;
	Integer s_small  = s - s_large;

	std::vector<Integer> small_plugs  = Random::partition(s_large, n_large);
	std::vector<Integer> large_plugs  = Random::partition(s_small, n_small);
	std::vector<Integer> random_plugs = Random::multiple(n_random, 3, 1'000'000'000);

	for(int i = 0; i < n_large; i++) small_plugs[i] += 2;
	for(int i = 0; i < n_small; i++) large_plugs[i] += 2;

	testOut << n << " " << (s + (n_large + n_small) * 2) << std::endl;
	std::vector<Integer> plugs;
	plugs.insert(plugs.end(), small_plugs.begin(), small_plugs.end());
	plugs.insert(plugs.end(), large_plugs.begin(), large_plugs.end());
	plugs.insert(plugs.end(), random_plugs.begin(), random_plugs.end());
	Random::shuffle(plugs);
	testOut << join(plugs) << std::endl;
}
