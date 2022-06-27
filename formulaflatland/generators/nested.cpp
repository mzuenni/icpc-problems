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
	vector<Integer> triangles = arguments["--triangles"].asIntegers();
	triangles.push_back(limN+7);

	Graph<NoData> res = cycle(4);
	priority_queue<entry> todo;
	todo.push({0, 0, 1, 2, 3});
	for (Integer it = 0; !todo.empty() && res.nodeCount() + 4 < limN; it++) {
		auto e = todo.top();
		todo.pop();
		int i = res.nodeCount();
		if (*lower_bound(all(triangles), i) == i) {
			res.append(cycle(3));
			res.append(cycle(4));
			res.append(cycle(4));

			res.addEdge(e.a, i);
			res.addEdge(e.b, i+1);
			res.addEdge(e.c, i+2);

			res.addEdge(i, i+3);
			res.addEdge(i+1, i+4);
			res.addEdge(i+2, i+5);

			res.addEdge(i+3, i+7);
			res.addEdge(i+4, i+8);
			res.addEdge(i+5, i+9);
			res.addEdge(i+6, i+10);

			todo.push({Random::integer(), e.a, i  , i+1, e.b});
			todo.push({Random::integer(), e.b, i+1, i+2, e.c});
			todo.push({Random::integer(), e.c, i+2, i+0, e.d});

			todo.push({Random::integer(),   i, i+3, i+4, i+1});
			todo.push({Random::integer(), i+1, i+4, i+5, i+2});
			todo.push({Random::integer(), i+2, i+5, i+6, i+3});

			todo.push({Random::integer(), i+3, i+7, i+8, i+4});
			todo.push({Random::integer(), i+4, i+8, i+9, i+5});
			todo.push({Random::integer(), i+5, i+9, i+10, i+6});
			todo.push({Random::integer(), i+6, i+10, i+7, i+3});
			todo.push({Random::integer(), i+7, i+10, i+9, i+8});
		} else {
			res.append(cycle(4));
			res.addEdge(e.a, i);
			res.addEdge(e.b, i+1);
			res.addEdge(e.c, i+2);
			res.addEdge(e.d, i+3);
			todo.push({Random::integer(), e.a, i  , i+1, e.b});
			todo.push({Random::integer(), e.b, i+1, i+2, e.c});
			todo.push({Random::integer(), e.c, i+2, i+3, e.d});
			todo.push({Random::integer(), e.d, i+3, i  , e.a});
			todo.push({Random::integer(),   i, i+3, i+2, i+1});
		}
	}
	res.setMinId(1);
	res.permutate();
	printPlanar(res);
}
