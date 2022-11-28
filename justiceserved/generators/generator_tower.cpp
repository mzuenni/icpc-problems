#include "validate.h"
using namespace std;

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(200000);
	Integer length = arguments["--length"].asInteger(100000000);
	judgeAssert(length > 2*n, "invalid parameters");

	testOut << n << endl;
	for (Integer i = 1; i <= n; i++) {
		testOut << i << " " << length-2*i << endl;
	}
}
