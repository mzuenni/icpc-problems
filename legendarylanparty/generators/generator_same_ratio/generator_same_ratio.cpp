#include "validate.h"
using namespace std;

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(200'000);
	Integer m = arguments["--m"].asInteger(1'000'000);
	Integer mul = arguments["--mul"].asInteger(3);

	judgeAssert(n*mul<=m,  "n*mul<=m");

	Integer nn = 0;
	Integer mm = 0;
	while (mm + nn + 1 < n) {
		nn++;
		mm += nn;
	}
	testOut << nn << " " << mul*mm << endl;
	for (Integer i = 1; i <= nn; i++) {
		testOut << i << " " << mul*i << endl;
	}
}
