#include "validate.h"
using namespace std;

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer t = arguments["--t"].asInteger(Random::integer(1, 100'001));
	Integer ns = arguments["--ns"].asInteger(1'000'000);
	Integer lim = arguments["--lim"].asInteger(99'999);
	
	testOut << t << endl;
	auto nss = Random::partition(ns, t);
	for (Integer n : nss) {
		vector<Integer> parts = Random::multiple(n, 1, lim+1);
		Integer sum = 0;
		for (Integer x : parts) sum += x;
		for (; sum < 3; sum++) Random::select(parts)++;
		testOut << n << endl;
		testOut << parts << endl;
	}
}
