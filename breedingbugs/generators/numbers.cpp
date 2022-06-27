#include "validate.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

int main(int argc, char **argv) {
	using namespace Generator;
	Generator::init(argc, argv);
	
	Integer n = arguments["--n"].asInteger();
	auto arg = arguments["--numbers"];
	vector<Integer> candidates;
	for (Integer i = 0; i < arg.parameterCount(); i++) candidates.push_back(arg[i].asInteger());
	
	vector<Integer> out(n);
	for (Integer i = 0; i < n; i++) out[i] = Random::select(all(candidates));

	testOut << n << endl;
	testOut << join(all(out)) << endl;
}
