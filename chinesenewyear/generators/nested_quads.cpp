#include "validate.h"
#include "graph_gen.h"
#include "gadget.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

struct entry {
	Integer id, a, b, c, d;
	bool operator<(const entry& o) const {
		return id < o.id;
	}
};

int main(int argc, char** argv) {
	using namespace Generator;
	Generator::init(argc, argv);

	Integer limN = arguments["--n"].asInteger(100000);

	Graph<NoData> res = cycle(4);
	priority_queue<entry> todo;
	todo.push({0, 0, 1, 2, 3});
	while (!todo.empty() && res.nodeCount() + 4 < limN) {
		auto e = todo.top();
		todo.pop();
		int i = res.nodeCount();
		res.append(cycle(4));
		res.addEdge(e.a, i);
		res.addEdge(e.b, i+1);
		res.addEdge(e.c, i+2);
		res.addEdge(e.d, i+3);
		todo.push({Random::integer(), e.a, i  , i+1, e.b});
		todo.push({Random::integer(), e.b, i+1, i+2, e.c});
		todo.push({Random::integer(), e.c, i+2, i+3, e.d});
		todo.push({Random::integer(), e.d, i+3, i  , e.a});
	}
	res.setMinId(1);
	res.permutate();
	printPlanar(res);
}
