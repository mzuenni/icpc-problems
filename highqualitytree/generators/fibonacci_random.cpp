#include "validate.h"
#include "graph_gen.h"
using namespace std;

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(200000);

	deque<Graph<NoData>> fib;
	fib.push_back(clique(1));
	fib.push_back(clique(2));
	for (Integer i = 2; 1 + fib[i-2].nodeCount() + fib[i - 1].nodeCount() <= n; i++) {
		Graph tmp(1);
		tmp.append(fib[i-2]);
		tmp.addEdge(0, 1);
		Integer next = tmp.nodeCount();
		tmp.append(fib[i-1]);
		tmp.addEdge(0, next);
		fib.push_back(tmp);
	}
	while (fib.back().nodeCount() < n) {
		// don't add to root!
		Integer i = Random::integer(1, fib.back().nodeCount());
		if (fib.back().degree(i) < 3) {
			Integer next = fib.back().nodeCount();
			fib.back().append(clique(1));
			fib.back().addEdge(i, next);
		}
	}
	auto g = fib.back();

	vector<Integer> perm(g.nodeCount());
	iota(perm.begin(), perm.end(), 0);
	Random::shuffle(next(perm.begin()), perm.end());
	g.permutate(perm);

	g.setMinId(1);
	testOut << g.nodeCount() << endl;
	for (auto e : g.getEdges()) testOut << e << endl;
}
