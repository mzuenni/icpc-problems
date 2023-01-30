#include "validate.h"
using namespace std;

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(200'000);
	Integer m = arguments["--m"].asInteger(1'000'000);
	Integer c = arguments["--c"].asInteger(1'000'001);

	judgeAssert(m >= n,  "m >= n");
	vector<Integer> sockets(n, 1);
	for (Integer i = n; i < m; i++) Random::select(sockets)++;

	testOut << n << " " << m << endl;
	for (Integer mi : sockets) {
		testOut << Random::integer(1, c) << " " << mi << endl;
	}
}
