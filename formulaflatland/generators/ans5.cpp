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

	Integer n = arguments["--n"].asInteger(100000-2);
    assert(n > 4);
    assert((n-2) % (4*3) == 0);
	Integer x = n / 4;
	assert(x % 3 == 0);

	Graph<NoData> res = cycle(x).append(cycle(x)).append(cycle(2*x));
	for (Integer i = 0, j = x, k = 2*x; i < x; i++, j++, k+=2) {
		res.addEdge(i, k);
		res.addEdge(j, k+1);
	}
	res.append(independent(2));
	Integer y = x * 4;
	Integer z = y + 1;
	for (Integer i = 0, j = x; i + 2 < x; i+=3, j+=3) {
		res.addEdge(i + 2, y);
		res.addEdge(j + 2, z);
	}
	res.setMinId(1);
	res.permutate();
	printPlanar(res);
}
