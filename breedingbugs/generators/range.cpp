#include "validate.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

int main(int argc, char **argv) {
	using namespace Generator;
	Generator::init(argc, argv);

	Integer first = arguments["--first"].asInteger();
	Integer n = arguments["--n"].asInteger();
	vector<Integer> out(n);
	for (Integer i = 0; i < n; i++) out[i] = first + i;

	Random::shuffle(all(out));

	testOut << n << endl;
	testOut << join(all(out)) << endl;
}
