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

	Integer a = arguments["--a"].asInteger(3*19*19*19);
	Integer b = arguments["--b"].asInteger(3*19*19);
	Integer c = arguments["--c"].asInteger(3*19);
	assert(4*(a+b+c+6)+4 <= 100000);
	assert(a >= 5);
	assert(b >= 5);
	assert(c >= 5);
	assert(a % 3 == 0);
	assert(b % 3 == 0);
	assert(c % 3 == 0);

	vector<Integer> length = {a,b,c,6};

	Graph<NoData> res = cycle(4);

	for (Integer it = 0; it < 4; it++) {
		Integer offset = res.nodeCount();
		Integer x = length[it];
		res.append(cycle(x));
		res.append(cycle(x));
		res.append(cycle(2*x));

		for (Integer i = offset, j = x+offset, k = 2*x+offset; i < x+offset; i++, j++, k+=2) {
			res.addEdge(i, k);
			res.addEdge(j, k+1);
		}
		for (Integer i = offset; i + 2 < x+offset; i+=3) {
			res.addEdge(i + 2, it);
		}
	}

	res.setMinId(1);
	res.permutate();
	printPlanar(res);
}
