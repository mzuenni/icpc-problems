#include "validate.h"
#include "graph_gen.h"
#include "gadget.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

bool connectedAndPlanar(Graph<NoData> orig) {
	orig.setMinId(0);
	Integer n = orig.nodeCount();

	using namespace boost;

	adj g(n);
	for (auto e : orig.getEdges()) add_edge(e.from, e.to, g);

	//Initialize the interior edge index
	property_map<adj, edge_index_t>::type e_index = get(edge_index, g);
	graph_traits<adj>::edges_size_type edge_count = 0;
	graph_traits<adj>::edge_iterator ei, ei_end;
	for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
		put(e_index, *ei, edge_count++);
	}

	make_connected(g);
	edge_count = 0;
	for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
		put(e_index, *ei, edge_count++);
	}
	if (edge_count != orig.edgeCount()) return false;

	std::vector<vec_t> embedding(n);
	return boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,
										boyer_myrvold_params::embedding = &embedding[0]);
}

int main(int argc, char** argv) {
	using namespace Generator;
	Generator::init(argc, argv);

	Integer n = arguments["--n"].asInteger(100'000);
	Graph<NoData> res;

	while (res.nodeCount() + 2 < n) {
		Integer k = Random::integer(2, std::min<Integer>(n - res.nodeCount(), 13));
		Integer m = Random::integer(max<Integer>(1 , 3*k - 6) - (k-1) + 1);
		Graph<NoData> tmp;
		do {
			tmp = randomTree(k).combine(randomGraph(k, m));
		} while (!connectedAndPlanar(tmp));
		res.append(tmp);
	}

	res.setMinId(1);
	res.permutate();
	printPlanar(res);
}
