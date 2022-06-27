#include "validate.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

int main(int argc, char **argv) {
	using namespace Generator;
	Generator::init(argc, argv);

	Integer n = arguments["--n"].asInteger();
	auto out = arguments["--other"].asIntegers();
	while (sz(out) < n) out.push_back(1);
	Random::shuffle(all(out));

	testOut << n << endl;
	testOut << join(all(out)) << endl;
}
