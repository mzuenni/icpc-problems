#include "validate.h"
#include "graph_gen.h"
using namespace std;

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(200000);

	auto tmp = completeTree(2, 2);
	auto g = tmp;
	while (g.nodeCount() + 2 < n) {
		tmp.setMinId(tmp.getMinId() + 2);
		g.combine(tmp);
	}

	vector<Integer> perm(g.nodeCount());
	iota(perm.begin(), perm.end(), 0);
	Random::shuffle(next(perm.begin()), perm.end());
	g.permutate(perm);

	g.setMinId(1);
	testOut << g.nodeCount() << endl;
	for (auto e : g.getEdges()) testOut << e << endl;
}
