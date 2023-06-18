#include "validate.h"
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

using namespace Generator;

int main(int argc, char **argv) {
	init(argc, argv);

	Integer n = arguments["--n"].asInteger(Random::integer(0, 200000));
	Integer q = arguments["--q"].asInteger(Random::integer(0, 200000));
	Integer p = arguments["--p"].asInteger(Random::integer(n + 1, 1000000));

	set<Integer> ps;
	while (sz(ps) < n) ps.insert(Random::integer(1, p));

	testOut << n << endl;
	testOut << join(all(ps)) << endl;
	testOut << q << endl;
	for (Integer i = 0; i < q ; i++) {
		testOut << Random::integer(1, n+1) << endl;
	}
}
