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

	Graph<NoData> res = hypercube(3).append(hypercube(3)).append(cycle(3));
	res.addEdge(16, 0);
	res.addEdge(17, 1);
	res.addEdge(18, 2);
	res.addEdge(16, 8);
	res.addEdge(17, 9);
	res.addEdge(18, 10);
	res.setMinId(1);
	res.permutate();
	printPlanar(res);
}
