#include "validate.h"
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

using namespace Generator;

int main(int argc, char **argv) {
	init(argc, argv);

	Integer n = arguments["--n"].asInteger(Random::integer(0, 200000));
	Integer q = arguments["--q"].asInteger(Random::integer(0, 200000));

	vector<Integer> pos(n);
	for (Integer i = 0; i < n; i++) {
		pos[i] = i+1;
	}

	testOut << n << endl;
	testOut << join(all(pos)) << endl;
	testOut << q << endl;
	for (Integer i = 0; i < q; i++) {
		testOut << 1 + (i % n) << endl;
	}
}
