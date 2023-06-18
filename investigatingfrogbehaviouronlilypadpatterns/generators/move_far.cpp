#include "validate.h"
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

using namespace Generator;

int main(int argc, char **argv) {
	init(argc, argv);

	Integer n = 2;
	Integer q = arguments["--q"].asInteger(Random::integer(0, 100000));
	Integer p = p = arguments["--p"].asInteger(Random::integer(n + 1, 1000000));

	set<Integer> ps = {p-2, p-1};

	testOut << n << endl;
	testOut << join(all(ps)) << endl;
	testOut << q << endl;
	for (Integer i = 0; i < q ; i++) {
		testOut << 1 + (i % 2) << endl;
	}
}
