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

	Integer l = arguments["--l"].asInteger(15);

	Graph<NoData> res = completeTree(l);
	Integer x = res.nodeCount();
	res.append(completeTree(l));

	res.addEdge(0, x);
	vector<Integer> leaves;
	for (Integer i = 0; i < res.nodeCount(); i++) {
		if (res.degree(i) < 3) leaves.push_back(i);
	}

	x = sz(leaves) / 2;
	for (Integer i = 0; i + 1 < x; i+=2) {
		res.addEdge(leaves[i], leaves[i+1]);
		res.addEdge(leaves[i+x], leaves[i+1+x]);
		res.addEdge(leaves[i], leaves[i+x]);
		res.addEdge(leaves[i+1], leaves[i+1+x]);
	}

	res.setMinId(1);
	res.permutate();
	printPlanar(res);
}
