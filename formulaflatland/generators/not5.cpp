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

	Graph<NoData> res = platon5;
	Integer n = res.nodeCount();
	res.append(platon5);
	res.addEdge(0, n);
	res.addEdge(2, n);
	res.setMinId(1);
	res.permutate();
	printPlanar(res);
}
