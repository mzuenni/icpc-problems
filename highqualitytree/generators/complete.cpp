#include "validate.h"
#include "graph_gen.h"
using namespace std;

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer l = arguments["--l"].asInteger(17);

	auto g = completeTree(l, 2);

	vector<Integer> perm(g.nodeCount());
	iota(perm.begin(), perm.end(), 0);
	Random::shuffle(next(perm.begin()), perm.end());
	g.permutate(perm);

	g.setMinId(1);
	testOut << g.nodeCount() << endl;
	for (auto e : g.getEdges()) testOut << e << endl;
}
