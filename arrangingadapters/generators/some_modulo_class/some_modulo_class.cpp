/**
 * This generates possibly plugs with length of one modulo 3 class, together with two modes.
 * - mode 0: random plugs
 * - mode 1: plugs with length relatively uniform
 * - mode 2 and 3: similar as mode 0 and 1, but we avoid the modolo 3 class in the parameter m
 * instead.
 */

#include "validate.h"

int main(int argc, char** argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n    = arguments["--n"].asInteger(Random::integer(20, 200'000));
	Integer s    = arguments["--s"].asInteger(Random::integer(1, 1'000'000'000));
	Integer m    = arguments["--m"].asInteger(Random::integer(0, 2));
	Integer mode = arguments["--mode"].asInteger(Random::integer(0, 3));

	Integer s1 = m == 0 ? 1 : 0;
	Integer s2 = m == 1 ? 2 : 1;

	if(mode == 0) {
		std::vector<Integer> v = Random::multiple(n, 1, (s - 100) / 3);
		for(int i = 0; i < n; i++) v[i] = v[i] * 3 + m;
		testOut << n << " " << s << std::endl;
		testOut << join(v) << std::endl;
	} else if(mode == 1) {
		std::vector<Integer> v = Random::multiple(n, 1, s / (2 * n) + 1);
		for(int i = 0; i < n; i++) v[i] = v[i] * 3 + m;
		testOut << n << " " << s << std::endl;
		testOut << join(v) << std::endl;
	} else if(mode == 2) {
		std::vector<Integer> v = Random::multiple(n, 1, (s - 100) / 3);
		for(int i = 0; i < n; i++) v[i] = v[i] * 3 + (Random::integer(1) == 0 ? s1 : s2);
		testOut << n << " " << s << std::endl;
		testOut << join(v) << std::endl;
	} else if(mode == 3) {
		std::vector<Integer> v = Random::multiple(n, 1, s / (2 * n) + 1);
		for(int i = 0; i < n; i++) v[i] = v[i] * 3 + (Random::integer(1) == 0 ? s1 : s2);
		testOut << n << " " << s << std::endl;
		testOut << join(v) << std::endl;
	}
}
