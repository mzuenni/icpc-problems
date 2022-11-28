#include "validate.h"
#include "graph_gen.h"
using namespace std;

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(200000);

	Graph<NoData> g = clique(1);
	vector<vector<Integer>> nodeByLevel = {{0}};
	while (g.nodeCount() < n) {
		Integer l = Random::integer(0, ssize(nodeByLevel));
		if (nodeByLevel[l].empty()) continue;
		Integer i = Random::integer(0, ssize(nodeByLevel[l]));
		Integer next = g.nodeCount();
		g.append(clique(1));
		g.addEdge(nodeByLevel[l][i], next);
		if (l + 1 == nodeByLevel.size()) nodeByLevel.emplace_back();
		nodeByLevel[l + 1].push_back(next);
		Integer maxDeg = 3;
		if (nodeByLevel[l][i] == 0) maxDeg--;
		if (g.degree(nodeByLevel[l][i]) == maxDeg) {
			swap(nodeByLevel[l].back(), nodeByLevel[l][i]);
			nodeByLevel[l].pop_back();
		}
	}
	vector<Integer> perm(g.nodeCount());
	iota(perm.begin(), perm.end(), 0);
	Random::shuffle(next(perm.begin()), perm.end());
	g.permutate(perm);

	g.setMinId(1);
	testOut << g.nodeCount() << endl;
	for (auto e : g.getEdges()) testOut << e << endl;
}
