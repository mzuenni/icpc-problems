#include "validate.h"
#include "graph_gen.h"
using namespace std;

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(200000);

	auto g = path(n-1).permutate().setMinId(1);
	cout << g.nodeCount() << endl;
	for (auto e : g.getEdges()) cout << e << endl;
}
