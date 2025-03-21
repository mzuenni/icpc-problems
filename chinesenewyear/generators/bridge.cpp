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

	Graph<NoData> res = platon4;
	Integer next = res.nodeCount();
	res.append(platon3);
	res.addEdge(0, next);

	res.setMinId(1);
	printPlanar(res);
}
