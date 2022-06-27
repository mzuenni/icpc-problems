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

	Integer w = arguments["--w"].asInteger(316);
	Integer h = arguments["--h"].asInteger(316);
	assert(w*h > 4);
	assert(w*h+1 <= 1000000);

	Graph<NoData> res = grid(w, h).range(0, w*h+1);
	for (Integer i = 0; i < w*h; i++) {
		if (res.degree(i) == 2)	res.addEdge(i, w*h);
	}
	res.setMinId(1);
	res.permutate();
	printPlanar(res);
}
