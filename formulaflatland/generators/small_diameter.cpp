#include "validate.h"
#include "graph_gen.h"
#include "gadget.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

int main(int argc, char** argv) {
	using namespace Generator;
	Generator::init(argc, argv);

	Integer n = arguments["--n"].asInteger(100000);
	assert(n > 4);
	assert(n % 2 == 0);

	Graph<NoData> res = cycle(n - 2).range(0, n);
	for (Integer i = 0; i < n - 2; i++) {
		res.addEdge(i, n - 1 - (i % 2));
	}
	res.setMinId(1);
	res.permutate();
	printPlanar(res);
}
