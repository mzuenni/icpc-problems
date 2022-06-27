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

	Integer n, m;
	std::cin >> n >> m;
	Graph<NoData> res(1, n+1);
	for (Integer i = 0; i < m; i++) {
		Integer a, b;
		std::cin >> a >> b;
		res.addEdge(a, b);
	}
	printPlanar(res);
}
