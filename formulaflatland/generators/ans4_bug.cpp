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

	Integer n = arguments["--n"].asInteger(100000-10);
    assert(n > 30);
    assert((n-30) % (2*4*3) == 0);
	Integer x = (n-30) / 8;
	assert(x % 3 == 0);

	Graph<NoData> res = cycle(x);
	res.append(cycle(x));
	res.append(cycle(2*x));
	res.append(cycle(x));
	res.append(cycle(x));
	res.append(cycle(2*x));
	for (Integer i = 0, j = x, k = 2*x; i < x; i++, j++, k+=2) {
		res.addEdge(i, k);
		res.addEdge(j, k+1);
		res.addEdge(i+4*x, k+4*x);
		res.addEdge(j+4*x, k+1+4*x);
	}
	res.append(independent(6));
	Integer y = 8*x;
	for (Integer i = 0, j = x; i + 2 < x; i+=3, j+=3) {
		res.addEdge(i + 2, y+0);
		res.addEdge(j + 2, y+1);
		res.addEdge(i + 2 + 4*x, y+2);
		res.addEdge(j + 2 + 4*x, y+3);
	}
	//diam
	res.addEdge(y + 0, y + 4);
	res.addEdge(y + 0, y + 5);
	res.addEdge(y + 2, y + 4);
	res.addEdge(y + 2, y + 5);

	//increase degree...
	res.append(cycle(6));
	res.append(cycle(6));
	res.append(cycle(2*6));
	Integer z = y + 6;
	for (Integer i = z, j = z+6, k = z+2*6; i < z+6; i++, j++, k+=2) {
		res.addEdge(i, k);
		res.addEdge(j, k+1);
	}
	res.addEdge(z, y + 4);
	res.addEdge(z + 3, y + 5);

	res.setMinId(1);
	res.permutate();
	printPlanar(res);
}
